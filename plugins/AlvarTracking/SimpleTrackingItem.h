#pragma once

#include <QPointF>
#include <QMap>

#include "TrackingItem.h"
#include "AlvarTracking.h"

namespace mtq {

	class SimpleTrackingItem : public TrackingItem
	{
		public:
			SimpleTrackingItem(int id, AlvarTracking *tracking);
			void nextFrame(QMap<int, AlvarMarker::Ptr> &markers);

			QPointF m_position;
		protected:
			bool m_lastIsDown;
			QPointF m_lastContactPos;

			bool m_isDown;
			bool m_hasMoved;

			float m_distanceToFloor;

		private:
			int m_id;

	};

}
