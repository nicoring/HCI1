#pragma once

#include <mtq/events/Event.h>
#include <QQuickItem>

namespace mtq {

	class MTQ_EXPORT_TYPE SceneViewRenderingDoneEvent : public Event
	{
		Q_OBJECT
		MTQ_EVENT(SceneViewRenderingDoneEvent)
	};

}
