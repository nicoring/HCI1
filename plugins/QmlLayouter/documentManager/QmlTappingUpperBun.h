#pragma once

#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>
#include <PositionEvents/PositionEventDispatcher.h>

namespace mtq {

	class QmlTappingUpperBun : public QQuickItem, public PositionEventDispatcher
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlTappingUpperBun, "layout")

		Q_PROPERTY(QVector2D lastDocPosition READ lastDocPosition WRITE setLastDocPosition)

		Q_PROPERTY(bool dragNDropActive READ dragNDropActive WRITE setDragNDropActive NOTIFY dragNDropActiveChanged)
		Q_PROPERTY(bool pickNDropActive READ pickNDropActive WRITE setPickNDropActive NOTIFY pickNDropActiveChanged)
		Q_PROPERTY(bool pilePickNDropActive READ pilePickNDropActive WRITE setPilePickNDropActive NOTIFY pilePickNDropActiveChanged)

	public:
		explicit QmlTappingUpperBun(QQuickItem *parent = 0);

		QVector2D lastDocPosition() const;
		void setLastDocPosition(QVector2D position);

		bool dragNDropActive() const;
		void setDragNDropActive(bool active);

		bool pickNDropActive() const;
		void setPickNDropActive(bool active);

		bool pilePickNDropActive() const;
		void setPilePickNDropActive(bool active);

		virtual bool dispatch(PositionEvent::Ptr event);

	signals:
		void moveDocument(QVector2D position);
		void contactMoveDocument(QVector2D position);
		void selectInRadius(QVector2D position);
		void deselectChildren();

		void dragNDropActiveChanged();
		void pickNDropActiveChanged();
		void pilePickNDropActiveChanged();

	private:
		void moveSelectedDocuments(QVector2D eventPosition);
		void contactMoveSelectedDocuments(QVector2D eventPosition);
		QVector2D m_lastDocPosition;
		bool m_dragNDropActive;
		bool m_pickNDropActive;
		bool m_pilePickNDropActive;
	};

}
