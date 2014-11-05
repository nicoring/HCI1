#include "TapsCreatingMouseArea.h"

#include <limits>

#include <mtq/core/EventDispatcher.h>
#include <PositionEvents/BodyEvents.h>
#include <PositionEvents/FloorEvents.h>
#include <PositionEvents/PointingEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(TapsCreatingMouseArea)

TapsCreatingMouseArea::TapsCreatingMouseArea()
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
	grabMouse();
	setWidth(10000);
	setHeight(10000);
	m_couldBeTap = false;
	m_doubleTap = false;
	m_couldBeDwell = false;
}

void TapsCreatingMouseArea::mousePressEvent(QMouseEvent *event)
{
	TapDownEvent *tapDown = new TapDownEvent();
	tapDown->position(QVector3D(event->globalPos()));
	tapDown->user(mtq::User(QString("masha")));
	MTQ_EMIT(tapDown);

	m_couldBeTap = true;
	m_couldBeDwell = true;
	m_dwellPosition = QVector3D(event->globalPos());

	QTimer::singleShot(200, this, SLOT(disableTap()));
	QTimer::singleShot(1500, this, SLOT(sendDwellIfPressed()));
}

void TapsCreatingMouseArea::mouseReleaseEvent(QMouseEvent *event)
{
	TapUpEvent *tapUp = new TapUpEvent();
	tapUp->position(QVector3D(event->globalPos()));
	tapUp->user(mtq::User(QString("masha")));
	MTQ_EMIT(tapUp);

	if(m_couldBeTap && !m_doubleTap) {
		TapEvent *posEvent = new TapEvent();
		posEvent->position(QVector3D(event->globalPos()));
		posEvent->user(mtq::User(QString("masha")));
		MTQ_EMIT(posEvent);
		m_couldBeTap = false;
	}
	m_doubleTap = false;
	m_couldBeDwell = false;
}

void TapsCreatingMouseArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	m_doubleTap = true;
	DoubleTapEvent *doubleTap = new DoubleTapEvent();
	doubleTap->position(QVector3D(event->globalPos()));
	doubleTap->user(mtq::User(QString("masha")));
	MTQ_EMIT(doubleTap);
}

void TapsCreatingMouseArea::mouseMoveEvent(QMouseEvent *event)
{
	ContactMoveEvent *moveEvent = new ContactMoveEvent();
	moveEvent->position(QVector3D(event->globalPos()));
	moveEvent->user(mtq::User(QString("masha")));
	MTQ_EMIT(moveEvent);
}

void TapsCreatingMouseArea::hoverMoveEvent(QHoverEvent * event) {
	MTQ_EMIT(new HeadPointingEvent(QVector3D(event->posF()), std::numeric_limits<qreal>::quiet_NaN(), mtq::User()));
	MTQ_EMIT(new HeadEvent(QVector3D(event->posF()), 0, mtq::User()));
}


void TapsCreatingMouseArea::disableTap()
{
	m_couldBeTap = false;
}

void TapsCreatingMouseArea::sendDwellIfPressed()
{
	if (m_couldBeDwell) {
		DwellEvent *dwell = new DwellEvent();
		dwell->position(m_dwellPosition);
		dwell->user(mtq::User(QString("masha")));
		MTQ_EMIT(dwell
				 );
	}
}
