#include "QmlOffscreenRenderer.h"

#include <mtq/core/EventDispatcher.h>
#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/UsersHolder.h>
#include <mtq/events/Actions.h>
#include <types/SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

MTQ_REGISTER_PLUGIN(QmlOffscreenRenderer)

QmlOffscreenRenderer::QmlOffscreenRenderer(const QString &pluginName, const Configuration &config)
	: Plugin(pluginName, config)
{
}

void QmlOffscreenRenderer::initialize()
{
	if (UsersHolder::instance().users().empty()) {
		MTQ_ERROR << "No users configured, won't process any skeletons!";
	} else {
		MTQ_REGISTER_FOR_EVENT(ReloadAction, SLOT(reload()));
		for(const User* user : UsersHolder::instance().users()) {
			m_sceneViews[user] = SceneRenderView::Ptr(new SceneRenderView(user->username, config()));
		}
		MTQ_REGISTER_FOR_EVENT(SkeletonSourceUpdateEvent, SLOT(skeletonUpdate(Event::Ptr)));
	}
}

void QmlOffscreenRenderer::reload()
{
	for (auto sceneview: m_sceneViews) {
		sceneview->reload();
	}
}

/// dispatches skeletons and forwards them to SceneRenderView
void QmlOffscreenRenderer::skeletonUpdate(Event::Ptr evt)
{
	if (m_sceneViews.contains(SkeletonSourceUpdateEvent::fromEvent(evt)->user())) {
		m_sceneViews[SkeletonSourceUpdateEvent::fromEvent(evt)->user()]->setSkeletonEvent(SkeletonSourceUpdateEvent::fromEvent(evt));
	} else {
		MTQ_WARNING << "Received SkeletonSourceUpdateEvent for unknown User!";
	}
}
