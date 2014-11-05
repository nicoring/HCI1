#include "AlvarTracking.h"

#include <Alvar.h>

#include <mtq/utils/Configuration.h>

#include "AlvarTracking/capture/ColorCapture.h"
#include "AlvarTracking/SimpleTrackingItem.h"

using namespace mtq;

MTQ_REGISTER_PLUGIN(AlvarTracking)

AlvarTracking::AlvarTracking(const QString &pluginName, const Configuration &config)
	: Plugin(pluginName, config),
	  m_rawWindow(NULL),
	  m_markerWindow(NULL),
	  m_capture(NULL)
{
}

AlvarTracking::~AlvarTracking()
{
	if (m_capture)
		delete m_capture;

	if (m_rawWindow)
		delete m_rawWindow;

	if (m_markerWindow)
		delete m_markerWindow;
}

void AlvarTracking::initialize()
{
	MTQ_INFO << "Running Alvar " << alvar::ALVAR_VERSION;

	m_trackedItems.push_back(new SimpleTrackingItem(config()["singleId"].toInt(), this));

	m_capture = new ColorCapture(config());

	if (config()["showRawImage"].toBool())
		m_rawWindow = new CvMatWindow();

	if (config()["showMarkerImage"].toBool())
		m_markerWindow = new CvMatWindow();
}

void AlvarTracking::run()
{
	while(isRunning()) {
		cv::Mat input;
		if (m_capture->read(input))
			processFrame(input);
		QCoreApplication::processEvents();
	}
}

void AlvarTracking::processFrame(cv::Mat &image)
{
	decreaseMarkerTTL();

	detectAlvar(image);

	for (int i=0;i<m_trackedItems.size();i++) {
		m_trackedItems.at(i)->nextFrame(m_markers);
	}

	visualizeMarkers(image);

	if (config()["showRawImage"].toBool())
		m_rawWindow->showCvMat(image);
}

void AlvarTracking::decreaseMarkerTTL() {
	foreach (AlvarMarker::Ptr marker, m_markers) {
		if (marker->m_remainingLifetime) marker->m_remainingLifetime--;
	}
}

void AlvarTracking::detectAlvar(cv::Mat &image)
{
	IplImage iplImg = image;

	m_markerDetector.Detect(&iplImg, &m_camera);

	for (auto detectedMarker = m_markerDetector.markers->begin(); detectedMarker != m_markerDetector.markers->end(); ++detectedMarker)
	{
		bool alreadyKnownMarker = m_markers.contains(detectedMarker->GetId());

		 AlvarMarker::Ptr current;

		if (!alreadyKnownMarker) // new marker found
		{
			current = (AlvarMarker::Ptr(new AlvarMarker()));
			m_markers[detectedMarker->GetId()] = current;
		} else {
			current = m_markers[detectedMarker->GetId()];
		}

		current->m_remainingLifetime = AlvarMarker::TTL;
		current->update(*detectedMarker);
	}
}

void AlvarTracking::visualizeMarkers(cv::Mat &image)
{
	cv::Mat temp = image.clone();

	foreach (auto & marker, m_markers)
	{
		if (!marker->isCurrent()) continue;
		// find marker center
		// sum up edges (hopefully 4) and divide by 4
		cv::Point2d pos = marker->center();

		double direction = atan2(marker->markerCorners().at(3).y - marker->markerCorners().at(0).y,
								 marker->markerCorners().at(3).x - marker->markerCorners().at(0).x);

		// draw center of marker
		cv::ellipse(temp, pos, cv::Size(10, 10), 0, 0, 360, cv::Scalar(255), -1);

		// draw direction of alvar-solution
		cv::line(temp,
				 pos, pos + cv::Point2d(cos(direction), sin(direction)) * 25,
				 cv::Scalar(255), 2);

		// draw z-bar and z coord
		double barHeight = 2 * (22 + marker->z());
		cv::rectangle(temp,
					  cv::Rect(pos.x+25, pos.y+35 - barHeight, 5, barHeight),
					  cv::Scalar(255), CV_FILLED);

		std::stringstream ss;
		//ss << "z: " << it->z();
		ss << "height: " << std::abs(marker->z()) * marker->edgeLength();
		cv::putText(temp, ss.str(), cv::Point(pos.x + 35, pos.y + 15), CV_FONT_NORMAL, 0.25, cv::Scalar(255, 255, 255));

		ss.str("");
		ss << "id: " << marker->id();
		cv::putText(temp, ss.str(), cv::Point(pos.x + 35, pos.y + 25), CV_FONT_NORMAL, 0.25, cv::Scalar(255, 255, 255));
	}

	if (config()["showMarkerImage"].toBool())
		m_markerWindow->showCvMat(temp);
}
