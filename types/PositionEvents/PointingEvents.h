#pragma once

#include "PositionEvents/PositionEvents.h"

namespace mtq {

	class MTQ_EXPORT_TYPE PointingEvent : public EnhancedPositionEvent {
		Q_OBJECT
	public:
		PointingEvent(const QVector3D &position, const qreal rotation, const User &user)
		  : EnhancedPositionEvent(position, rotation, user)
		{}

		PointingEvent(const QVector3D &position, const User &user)
		  : EnhancedPositionEvent(position, user)
		{}

		MTQ_EVENT(PointingEvent)
	};

	class MTQ_EXPORT_TYPE HeadPointingEvent : public PointingEvent {
		Q_OBJECT
	public:
		HeadPointingEvent(const QVector3D &position, const qreal rotation, const User &user)
		  : PointingEvent(position, rotation, user)
		{}

		HeadPointingEvent(const QVector3D &position, const User &user)
		  : PointingEvent(position, user)
		{}

		MTQ_EVENT(HeadPointingEvent)
	};

}
