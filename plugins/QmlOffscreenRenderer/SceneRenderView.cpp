#include "SceneRenderView.h"

#include <QGuiApplication>
#include <QImage>
#include <QScreen>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>

#include <mtq/core/Application.h>
#include <mtq/core/PluginRegistry.h>
#include <mtq/core/EventDispatcher.h>
#include <types/SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

static bool biggerZFirst(QQuickItem *lhs, QQuickItem *rhs)
{
	return lhs->z() > rhs->z();
}

SceneRenderView::SceneRenderView(QString name, Configuration config, QWindow *parent)
	: QQuickView(parent),
	  m_name(name),
	  m_config(config)
{
	setColor(Qt::black);
	setClearBeforeRendering( false );
	connect(this, SIGNAL(beforeRendering()), this, SLOT(beforeRenderingHandler()), Qt::DirectConnection);
	connect(this, SIGNAL(afterRendering()), this, SLOT(afterRenderingHandler()), Qt::DirectConnection);

	rootContext()->setContextProperty("contextUsername", name);
	reload(false);
	show();
}

/// is called from QmlOffscreenRenderer
void SceneRenderView::setSkeletonEvent(SkeletonSourceUpdateEvent::Ptr newSkeletonEvent)
{
	m_skeletonMutex.lock();
		m_currentSkeletonEvent = newSkeletonEvent;
	m_skeletonMutex.unlock();
}

void SceneRenderView::show()
{
	QQuickView::setResizeMode(QQuickView::SizeRootObjectToView);

	setHeight(config()["height"].toInt());
	setWidth(config()["width"].toInt());
	QQuickView::show();

	moveToScreen();
}

void SceneRenderView::beforeRenderingHandler()
{
	if (!m_renderFbo && !config()["onScreen"].toBool()) {
		// Initialize the buffers and renderer
		QOpenGLFramebufferObjectFormat format;
		format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
		m_renderFbo.reset(new QOpenGLFramebufferObject( size(), QOpenGLFramebufferObject::NoAttachment) );
		setRenderTarget(m_renderFbo.data());
	}
}

void SceneRenderView::afterRenderingHandler()
{
	if ((!m_currentSkeletonEvent.isNull()) && (!m_renderFbo.isNull())) {
		QImage fbo_content = m_renderFbo->toImage();
		PrePolygonEnhancedSkeletonEvent *event = new PrePolygonEnhancedSkeletonEvent();
		event->visibilityImage(fbo_content);
		m_skeletonMutex.lock();
			event->skeleton(m_currentSkeletonEvent->skeleton());
			event->user(m_currentSkeletonEvent->user());
			m_currentSkeletonEvent.clear();
		m_skeletonMutex.unlock();
		MTQ_EMIT(event);
	}
}

void SceneRenderView::moveToScreen()
{
	if (config()["onScreen"].toBool()) {
		QScreen *screen = config()["primaryScreen"].toBool() ? QGuiApplication::primaryScreen() : screen = QGuiApplication::screens().last();
		QRect screenResolution = screen->geometry();
		setPosition(screenResolution.left() + (screenResolution.width()  - width())  / 2,
					screenResolution.top()  + (screenResolution.height() - height()) / 2);
	} else {
		setPosition(26000, 26000);
	}
}

void SceneRenderView::reload(bool clearCache)
{
	if (clearCache)
		engine()->clearComponentCache();

	setSource(QUrl::fromLocalFile(QDir::currentPath() + "/offscreenQml.qml"));
}

const Configuration SceneRenderView::config() const
{
	return m_config;
}
