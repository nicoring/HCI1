#pragma once

#include "mtq/events/Event.h"

namespace mtq {

	class MTQ_EXPORT_MTQ ReloadAction : public Event
	{
		Q_OBJECT
		MTQ_EVENT(ReloadAction)
	};

}
