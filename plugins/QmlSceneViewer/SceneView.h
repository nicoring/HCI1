#pragma once

#include <QQuickView>

#include <mtq/utils/Configuration.h>
#include <mtq/core/PluginRegistry.h>

#include "PositionEvents/PositionEventDispatcher.h"

namespace mtq {

	class QmlSceneViewer;

	class SceneView : public QQuickView
	{
	Q_OBJECT
	public:
		SceneView(QString name, Configuration config, QWindow *parent = 0);

	public slots:
		void show();

	protected:
		void moveToScreen();
		void reload(bool clearCache = true);

	private:
		const Configuration config() const;

		QList<PositionEventDispatcher *> touchedItems(PositionEvent::Ptr event);
		void traverseChildren(QQuickItem *item, QList<PositionEventDispatcher *> &accumulator, QPointF scenePos);

		QString m_name;
		Configuration m_config;

		void updateRecursive(QQuickItem *item);

	private slots:
		void renderingDone();

	friend class QmlSceneViewer;
	};

}
