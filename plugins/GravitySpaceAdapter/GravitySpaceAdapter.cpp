#include "GravitySpaceAdapter.h"

#include <limits>
#include <GravitySpace.h>
#include <boost/filesystem.hpp>

#include <mtq/core/EventDispatcher.h>
#include <GravitySpaceTypes/GravitySpaceEvents.h>
#include <PositionEvents/PositionEvents.h>
#include <PositionEvents/FloorEvents.h>

namespace gs = GravitySpace;

using namespace mtq;

MTQ_REGISTER_PLUGIN(GravitySpaceAdapter)

GravitySpaceAdapter::GravitySpaceAdapter(const QString &pluginName, const Configuration &config)
	: Plugin(pluginName, config),
	  m_gravitySpace(gs::Framework::retrieve())
{
	for (int i=0; i<256; i++) {
		m_colorTable.push_back(qRgb(i, i, i));
	}
}

void GravitySpaceAdapter::initialize()
{
	gs::SettingsPtr settings = m_gravitySpace->settings();

	// Common settings
	settings->setProperty<float>(L"preprocessor::merge distance", 20.0f);
	settings->setProperty<bool>(L"use console", config()["useConsole"].toBool());

	QString rootDir = config()["rootDir"].toString();
	boost::filesystem::path gsRoot(rootDir.toStdWString());

	// Calibration
	settings->setProperty<std::wstring>(L"camera::calibration file", (gsRoot / L"config/calib_projector_camera.gscalib").wstring());
	settings->setProperty<std::wstring>(L"camera::precalibration file", (gsRoot / L"config/calib_physical_projector.gscalib").wstring());
	settings->setProperty<std::wstring>(L"touch floor::calibration file", (gsRoot / L"config/calib_projector_camera.gscalib").wstring());

	settings->setProperty<bool>(L"sole identifier::use cuda", true);
	settings->setProperty<bool>(L"sole identifier::use fourier registration", true);

	// Sole identifier plugin (always on)
	m_gravitySpace->addPlugin<gs::GaitRecognitionPlugin>();
	m_gravitySpace->addPlugin<gs::SoleIdentificationPlugin>();

	// Sole identifier plugin options
	settings->setProperty<std::wstring>(L"users::file", (gsRoot / L"users/users.gsu").wstring());
	settings->setProperty<bool>(L"use fly camera", false);

    //Enable other plugins that might be helpful
	m_gravitySpace->addPlugin<gs::TiltingPlugin>();

	m_gravitySpace->initialize();

	connectCallbacks();

	MTQ_INFO << "Initialized GravitySpace-Framework.";
}

void GravitySpaceAdapter::run()
{
	m_gravitySpace->run();
	m_gravitySpace->camera()->isActive() || m_gravitySpace->camera()->activate();

	MTQ_INFO << "Started GravitySpace-Framework.";
}

void GravitySpaceAdapter::cleanUp()
{
	m_gravitySpace->camera()->isActive() && m_gravitySpace->camera()->deactivate();
	m_gravitySpace->stop();
}

void GravitySpaceAdapter::connectCallbacks()
{
	if (config()["sendPositionEvents"].toBool()) {
		m_gravitySpace->touchFloor()->callOnContactDown(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::ContactDown, _1));
		m_gravitySpace->touchFloor()->callOnContactMove(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::ContactMove, _1));
		m_gravitySpace->touchFloor()->callOnContactUp(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::ContactUp, _1));

		m_gravitySpace->plugin<gs::GaitRecognitionPlugin>()->callOnTapDown(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::TapDown, _1));
		m_gravitySpace->plugin<gs::GaitRecognitionPlugin>()->callOnTapUp(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::TapUp, _1));
		m_gravitySpace->plugin<gs::GaitRecognitionPlugin>()->callOnTap(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::Tap, _1));
		m_gravitySpace->plugin<gs::GaitRecognitionPlugin>()->callOnDoubleTap(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::DoubleTap, _1));
		m_gravitySpace->plugin<gs::GaitRecognitionPlugin>()->callOnDwell(boost::bind(&GravitySpaceAdapter::processContactEvent, this, EventKind::Dwell, _1));
	}

	if (config()["sendFrameImageEvents"].toBool()) {
		m_gravitySpace->contactProcessor()->callOnProcessing(boost::bind(&GravitySpaceAdapter::processFrameCapturedEvent, this, _1));
	}

	if (config()["quitOnExitGesture"].toBool()) {
		m_gravitySpace->plugin<gs::Users>()->callAsyncOnUserExitGesture(boost::bind(&GravitySpaceAdapter::processExitGesture, this));
	}

    if (m_gravitySpace->plugin<gs::Users>()){
        m_gravitySpace->plugin<gs::Users>()->callOnUserJoined(boost::bind(&GravitySpaceAdapter::processUserEvent, this, UserEventKind::UserJoined, _1));
        m_gravitySpace->plugin<gs::Users>()->callOnUserIdentified(boost::bind(&GravitySpaceAdapter::processUserEvent, this, UserEventKind::UserIdentified, _1));
        m_gravitySpace->plugin<gs::Users>()->callOnUserLeft(boost::bind(&GravitySpaceAdapter::processUserEvent, this, UserEventKind::UserLeft, _1));
    }
}

void GravitySpaceAdapter::processContactEvent(const EventKind kind, const GravitySpace::ContactPtr &contact) const
{
	gs::SoleIdentifyResultPtr identity = contact->extension<gs::SoleIdentification>()->result();
	gs::TiltingPtr tilting = contact->extension<gs::Tilting>();

	FloorEvent *event = createEvent(kind);
	event->id(contact->id());
	event->position(QVector3D(projectToFloor(contact->centerOfPressure())));
	event->rotation(retrieveRotationFromSoleIdentifyResult(identity));
	event->size(QSize(contact->bbox().extents.x, contact->bbox().extents.y));
	event->user(retrieveUserFromSoleIdentifyResult(identity));

	event->tiltAngle(tilting->angle());
	event->tiltDirection(
				QVector2D(tilting->direction()(0),
						  tilting->direction()(1)));
	event->tiltMovingDirection(
				QVector2D(tilting->movingDirection()(0),
						  tilting->movingDirection()(0)));
	event->tiltMovingSpeed(tilting->movingSpeed());

	if (config()["attachContactImage"].toBool())
		event->image(imageFromCvMat(contact->image()));

	MTQ_EMIT(event)
}

void GravitySpaceAdapter::processUserEvent(const UserEventKind kind, const GravitySpace::UserPtr &user) const
{
    MTQ_DEBUG << "GsUserEvent of Type " << kind;

}

void GravitySpaceAdapter::processFrameCapturedEvent(const GravitySpace::ProcessingDataPtr &data) const
{
	MTQ_EMIT(new GravitySpaceFrameImageEvent(imageFromCvMat(data->quarter_image)))
}

void GravitySpaceAdapter::processExitGesture() const
{
	MTQ_DEBUG << "Received GravitySpace exit gesture. Quitting application.";
	QApplication::quit();
}

FloorEvent* GravitySpaceAdapter::createEvent(const EventKind kind) const
{
	switch(kind) {
	case EventKind::ContactDown:
		return new ContactDownEvent();
	case EventKind::ContactMove:
		return new ContactMoveEvent();
	case EventKind::ContactUp:
		return new ContactUpEvent();

	case EventKind::TapDown:
		return new TapDownEvent();
	case EventKind::TapUp:
		return new TapUpEvent();
	case EventKind::Tap:
		return new TapEvent();
	case EventKind::DoubleTap:
		return new DoubleTapEvent();

	case EventKind::Dwell:
		return new DwellEvent();

	default:
		return new FloorEvent();
	}
}

QPointF GravitySpaceAdapter::projectToFloor(const GravitySpace::Point2f &point) const
{
	gs::Point2f projected = m_gravitySpace->touchFloor()->project(point);
	return QPointF(projected.x, projected.y);
}

const User GravitySpaceAdapter::retrieveUserFromSoleIdentifyResult(const GravitySpace::SoleIdentifyResultPtr &soleIdentifyResult) const
{
	if (soleIdentifyResult) {
		return User(QString::fromWCharArray(soleIdentifyResult->user->name().c_str()));
	} else {
		return User();
	}
}

qreal GravitySpaceAdapter::retrieveRotationFromSoleIdentifyResult(const GravitySpace::SoleIdentifyResultPtr &soleIdentifyResult) const
{
	if (soleIdentifyResult &&
		soleIdentifyResult->tip.x == soleIdentifyResult->tip.x &&
		soleIdentifyResult->tip.y == soleIdentifyResult->tip.y &&
		soleIdentifyResult->heel.x == soleIdentifyResult->heel.x &&
		soleIdentifyResult->heel.y == soleIdentifyResult->heel.y) {
		return std::atan2(soleIdentifyResult->tip.x - soleIdentifyResult->heel.x, soleIdentifyResult->heel.y - soleIdentifyResult->tip.y);
	} else {
		return std::numeric_limits<qreal>::quiet_NaN();
	}
}

QImage GravitySpaceAdapter::imageFromCvMat(const cv::Mat &matrix) const
{
	QImage image(matrix.data, matrix.cols, matrix.rows, QImage::Format_Indexed8);
	image.detach();
	image.setColorTable(m_colorTable);
	return image;
}
