#include "SceneView.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QScreen>

#include <mtq/core/Application.h>
#include <mtq/core/PluginRegistry.h>
#include <mtq/core/EventDispatcher.h>
#include <mtq/utils/Configuration.h>

#include <types/RenderingEvents/SceneViewRenderingDoneEvent.h>

#include "core/QmlMtqSingelton.h"
#include "core/QmlRootItem.h"
#include "QmlSceneViewer.h"

using namespace mtq;

static bool biggerZFirst(QQuickItem *lhs, QQuickItem *rhs)
{
	return lhs->z() > rhs->z();
}

SceneView::SceneView(QString name, Configuration config, QWindow *parent)
	: QQuickView(parent),
	  m_name(name),
	  m_config(config)
{
	qmlRegisterSingletonType<QmlMtqSingelton>("mtq.core", 1, 0, "Mtq",
											  mtq_singletontype_provider);
	setColor(Qt::black);
	engine()->setOfflineStoragePath(config["LocalStoragePath"].toString());
	reload(false);
	show();

	connect(this, SIGNAL(afterRendering()), this, SLOT(renderingDone()));
}

void SceneView::show()
{
	QQuickView::setResizeMode(QQuickView::SizeRootObjectToView);

	if (config()["fullScreen"].toBool()) {
		QQuickView::showFullScreen();
	} else {
		setHeight(config()["height"].toInt());
		setWidth(config()["width"].toInt());
		QQuickView::show();
	}

	moveToScreen();
}

void SceneView::moveToScreen()
{
	QScreen *screen = config()["primaryScreen"].toBool() ? QGuiApplication::primaryScreen() : screen = QGuiApplication::screens().last();
	QRect screenResolution = screen->geometry();

	if (config()["fullScreen"].toBool() && !config()["primaryScreen"].toBool())
		resize(screenResolution.width() + 1, screenResolution.height());

	setPosition(screenResolution.left() + (screenResolution.width() - width()) / 2,
				screenResolution.top() + (screenResolution.height() - height()) / 2);
}

void SceneView::reload(bool clearCache)
{
	if (clearCache)
		engine()->clearComponentCache();

	setSource(QUrl("qrc:/qml/QmlViewer.qml"));
	QmlRootItem *root = contentItem()->childItems().last()->findChild<QmlRootItem *>("RootItem");
	if (root) {
		root->setName(m_name);
		connect(this, SIGNAL(beforeRendering()), root, SLOT(frameStarted()));
		connect(this, SIGNAL(afterRendering()), root, SLOT(frameFinished()));
	}
}

QList<PositionEventDispatcher *> SceneView::touchedItems(PositionEvent::Ptr event)
{
	QList<PositionEventDispatcher *> items;
	QPointF scenePos = event->position2D().toPointF();

	traverseChildren(contentItem(), items, scenePos);
	return items;
}

void SceneView::traverseChildren(QQuickItem *item, QList<PositionEventDispatcher *> &accumulator, QPointF scenePos)
{
	if (!item) return;

	if (PositionEventDispatcher *eventDispatcher = dynamic_cast<PositionEventDispatcher *>(item)) {
		if (item->contains(item->mapFromScene(scenePos))) {
			accumulator.append(eventDispatcher);
		}
	}

	QList<QQuickItem *> items = item->childItems();
	qStableSort(items.begin(), items.end(), biggerZFirst);

	for (int i = 0; i < items.size(); ++i) {
		QQuickItem *localItem = items[i];
		traverseChildren(localItem, accumulator, scenePos);
	}
}

const Configuration SceneView::config() const
{
	return m_config;
}


void SceneView::renderingDone()
{
	MTQ_EMIT(new SceneViewRenderingDoneEvent());
}
