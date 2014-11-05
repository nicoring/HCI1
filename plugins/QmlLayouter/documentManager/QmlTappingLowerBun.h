#pragma once

#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>
#include <PositionEvents/PositionEventDispatcher.h>

namespace mtq {

	class QmlTappingLowerBun : public QQuickItem, public PositionEventDispatcher
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlTappingLowerBun, "layout")

	public:
		explicit QmlTappingLowerBun(QQuickItem *parent = 0);
		virtual bool dispatch(PositionEvent::Ptr event);

	signals:
		void resetStackCounter();

	};

}

