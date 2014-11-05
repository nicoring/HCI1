#pragma once

#include "PositionEvents/PositionEvents.h"

namespace mtq {

	class MTQ_EXPORT_TYPE SolowheelEvent : public EnhancedPositionEvent
	{
		Q_OBJECT
	public:
		SolowheelEvent(const QVector3D &position, const qreal rotation)
		  : EnhancedPositionEvent(position, rotation)
		{}

		MTQ_EVENT(SolowheelEvent)
	};

}
