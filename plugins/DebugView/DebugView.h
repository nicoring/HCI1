#pragma once

#include <mtq/core/PluginRegistry.h>
#include <mtq/events/Event.h>

#include "DebugView/ShadowViewerWidget.h"

namespace mtq {

	class MTQ_EXPORT_PLUGIN DebugView : public Plugin
	{
		Q_OBJECT

		MTQ_PLUGIN(DebugView)

	public:
		~DebugView();
		void initialize();

	public slots:
		void handleSkeletonEvent(Event::Ptr event);

	private:
		ShadowViewerWidget *m_shadowViewer;
	};

}
