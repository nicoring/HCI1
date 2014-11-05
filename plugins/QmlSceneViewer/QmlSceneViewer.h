#pragma once

#include <mtq/core/PluginRegistry.h>
#include <mtq/events/Event.h>

#include "QmlSceneViewer/SceneView.h"

namespace mtq {

	class MTQ_EXPORT_PLUGIN QmlSceneViewer : public Plugin
	{
		Q_OBJECT
	public:
		virtual ~QmlSceneViewer();
		void initialize();

	public slots:
		void dispatch(Event::Ptr event);
		void reload();

	private:
		SceneView *m_sceneView;

		MTQ_PLUGIN(QmlSceneViewer)
	};

}
