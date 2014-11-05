#pragma once

#include <QQuickItem>
#include <PositionEvents/PositionEventDispatcher.h>

#include <mtq/core/PluginRegistry.h>

namespace mtq {

	class QmlEventDummy: public QQuickItem, public PositionEventDispatcher
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlEventDummy, "core")

	public:
		explicit QmlEventDummy(QQuickItem *parent = 0);

	public slots:
		virtual bool dispatch(PositionEvent::Ptr event);

	signals:
		void tap(QVector2D	position);
		void tapDown(QVector2D position);
		void tapUp();
		void contactMove(QVector2D position);
	};

}
