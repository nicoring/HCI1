#pragma once

#include "PositionEvents/PositionEvents.h"

namespace mtq {

	class MTQ_EXPORT_TYPE PositionEventDispatcher
	{
	public:
		virtual bool dispatch(PositionEvent::Ptr);
	};

}
