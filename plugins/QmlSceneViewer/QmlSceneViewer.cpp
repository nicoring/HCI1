#include "QmlSceneViewer.h"

#include <mtq/core/EventDispatcher.h>
#include <mtq/events/Actions.h>
#include <PositionEvents/PositionEvents.h>
#include <PositionEvents/PositionEventDispatcher.h>
#include <QQmlPropertyMap>
using namespace mtq;

MTQ_REGISTER_PLUGIN(QmlSceneViewer)

QmlSceneViewer::QmlSceneViewer(const QString &pluginName, const Configuration &config)
	: Plugin(pluginName, config),
	  m_sceneView(NULL)
{
}

QmlSceneViewer::~QmlSceneViewer()
{
	if (m_sceneView)
		delete m_sceneView;
}

void QmlSceneViewer::initialize()
{
	MTQ_REGISTER_FOR_EVENT(ReloadAction, SLOT(reload()));
	MTQ_REGISTER_FOR_EVENT(PositionEvent, SLOT(dispatch(Event::Ptr)));

	m_sceneView = new SceneView(pluginName(), config());
}

void QmlSceneViewer::dispatch(Event::Ptr event)
{
	PositionEvent::Ptr positionEvent = PositionEvent::fromEvent(event);
	QList<PositionEventDispatcher *> items = m_sceneView->touchedItems(positionEvent);
	foreach (PositionEventDispatcher *item, items) {
		if (item->dispatch(positionEvent))
			break;
	}
}

void QmlSceneViewer::reload()
{
	m_sceneView->reload();
}
