#pragma once

#include "QmlLayouter/layoutObjects/QmlLayoutObject.h"
#include <PositionEvents/PositionEventDispatcher.h>

#include <mtq/core/PluginRegistry.h>

namespace mtq {

	class QmlDocument : public QmlLayoutObject, public PositionEventDispatcher
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlDocument, "layout")

		Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)

	public:
		explicit QmlDocument(QQuickItem *parent = 0);

		bool selected() const;
		void setSelected(bool selected);

		virtual bool dispatch(PositionEvent::Ptr event);

	signals:
		void selectedChanged();

		void tap(QVector2D	position);
		void tapDown(QVector2D position);
		void doubleTap(QVector2D position);
		void tapUp();
		void contactMove(QVector2D position);

		void dwell(QVector2D position);

	protected:
		bool m_selected;


	};

}
