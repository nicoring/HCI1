#pragma once

#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>

namespace mtq {
	class QmlPanZoomRootItem : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlPanZoomRootItem, "core")

		Q_PROPERTY(bool isPanZoomRootItem READ isPanZoomRootItem)

	public:
		QmlPanZoomRootItem(QQuickItem *parent = 0);
		bool isPanZoomRootItem() const;
	};

}
