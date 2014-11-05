#pragma once

#include "PositionEvents/PositionEvents.h"

namespace mtq {

	class MTQ_EXPORT_TYPE HeadEvent : public EnhancedPositionEvent
	{
		Q_OBJECT
	public:
		HeadEvent(const QVector3D &position, const qreal rotation, const User &user)
		  : EnhancedPositionEvent(position, rotation, user)
		{}

		MTQ_EVENT(HeadEvent)
	};

}
