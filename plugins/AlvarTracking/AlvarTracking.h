#pragma once

#include <Alvar.h>
#include <MarkerDetector.h>

#include <mtq/core/PluginRegistry.h>

#include "AlvarTracking/utils/CvMatWindow.h"
#include "AlvarTracking/capture/Capture.h"
#include "AlvarTracking/TrackingItem.h"

namespace mtq {

	class MTQ_EXPORT_PLUGIN AlvarTracking : public Plugin
	{
		Q_OBJECT
	public:
		~AlvarTracking();
		void initialize();
		void run();

	private:
		void processFrame(cv::Mat & img);
		void decreaseMarkerTTL();
		void detectAlvar(cv::Mat &image);
		void visualizeMarkers(cv::Mat &image);
		void checkForLostMarkers();

		alvar::Camera m_camera;
		CvMatWindow *m_rawWindow;
		CvMatWindow *m_markerWindow;
		Capture *m_capture;
		std::vector<TrackingItem*> m_trackedItems;
		alvar::MarkerDetector<alvar::MarkerData> m_markerDetector;
		QMap<int, AlvarMarker::Ptr> m_markers;

		MTQ_PLUGIN(AlvarTracking)
	};

}
