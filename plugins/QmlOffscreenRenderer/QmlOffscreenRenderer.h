#pragma once

#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/User.h>
#include <mtq/events/Event.h>

#include "QmlOffscreenRenderer/SceneRenderView.h"

namespace mtq {

	class MTQ_EXPORT_PLUGIN QmlOffscreenRenderer : public Plugin
	{
		Q_OBJECT

		MTQ_PLUGIN(QmlOffscreenRenderer)

	public:
		void initialize();

	public slots:
		void reload();
		void skeletonUpdate(Event::Ptr evt);

	private:
		QHash<const User*, SceneRenderView::Ptr> m_sceneViews;
	};

}
