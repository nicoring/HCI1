#pragma once

#include <boost/shared_ptr.hpp>
#include <general/forward_declarations.h>

#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/User.h>
#include <PositionEvents/FloorEvents.h>

namespace mtq {

	class MTQ_EXPORT_PLUGIN GravitySpaceAdapter : public Plugin
	{
		Q_OBJECT
	public:
		void initialize();
		void run();
		void cleanUp();

	private:
		typedef enum {ContactDown, ContactMove, ContactUp, TapDown, TapUp, Tap, DoubleTap, Dwell} EventKind;
        typedef enum {UserJoined, UserIdentified, UserLeft} UserEventKind;
		void connectCallbacks();

		void processContactEvent(const EventKind kind, const GravitySpace::ContactPtr &contact) const;
        void processUserEvent(const UserEventKind kind, const GravitySpace::UserPtr &user) const;

		void processFrameCapturedEvent(const GravitySpace::ProcessingDataPtr &data) const;
		void processExitGesture() const;

		FloorEvent* GravitySpaceAdapter::createEvent(const EventKind kind) const;
		QPointF projectToFloor(const GravitySpace::Point2f &point) const;
		const User retrieveUserFromSoleIdentifyResult(const GravitySpace::SoleIdentifyResultPtr &soleIdentifyResult) const;
		qreal retrieveRotationFromSoleIdentifyResult(const GravitySpace::SoleIdentifyResultPtr &soleIdentifyResult) const;
		QImage imageFromCvMat(const cv::Mat &matrix) const;

		GravitySpace::FrameworkPtr m_gravitySpace;
		QVector<QRgb> m_colorTable;

		MTQ_PLUGIN(GravitySpaceAdapter)
	};

}
