#pragma once

#include <QOpenGLFramebufferObject>
#include <QMutex>
#include <QQuickView>

#include <mtq/core/PluginRegistry.h>
#include <mtq/utils/Configuration.h>

#include <types/SkeletonTypes/Skeleton.h>
#include <types/SkeletonTypes/SkeletonEvents.h>

namespace mtq {

	class QmlOffscreenRenderer;

	class SceneRenderView : public QQuickView
	{
	Q_OBJECT

	public:
		typedef QSharedPointer<SceneRenderView> Ptr;
		SceneRenderView(QString name, Configuration config, QWindow *parent = 0);
		void setSkeletonEvent(SkeletonSourceUpdateEvent::Ptr newSkeletonEvent);

	public slots:
		void show();
		void beforeRenderingHandler();
		void afterRenderingHandler();

	protected:
		void moveToScreen();
		void reload(bool clearCache = true);
		QMutex m_skeletonMutex;
		SkeletonSourceUpdateEvent::Ptr m_currentSkeletonEvent;

	private:
		const Configuration config() const;
		QString m_name;
		Configuration m_config;
		QScopedPointer<QOpenGLFramebufferObject> m_renderFbo;

	friend class QmlOffscreenRenderer;
	};

}
