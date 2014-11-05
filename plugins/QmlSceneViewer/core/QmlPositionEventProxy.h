#pragma once

#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>
#include <mtq/events/Event.h>

namespace mtq {

	class QmlPositionEventProxy : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlPositionEventProxy, "core")

		Q_PROPERTY(QString eventType READ eventType WRITE setEventType NOTIFY eventTypeChanged)
		Q_PROPERTY(qreal xOffset READ xOffset WRITE setXOffset NOTIFY xOffsetChanged)
		Q_PROPERTY(qreal yOffset READ yOffset WRITE setYOffset NOTIFY yOffsetChanged)
		Q_PROPERTY(qreal coordinateScaling READ coordinateScaling WRITE setCoordinateScaling NOTIFY coordinateScalingChanged)

	public:
		explicit QmlPositionEventProxy(QQuickItem *parent = 0);

		QString eventType() const;
		void setEventType(QString typeName);
		qreal xOffset() const;
		void setXOffset(qreal offset);
		qreal yOffset() const;
		void setYOffset(qreal offset);
		qreal coordinateScaling() const;
		void setCoordinateScaling(qreal scale);

	signals:
		void eventTypeChanged();
		void xOffsetChanged();
		void yOffsetChanged();
		void coordinateScalingChanged();

	public slots:
		void receivePositionEvent(Event::Ptr event);

	private:
		QString m_eventType;
		bool m_filterActive;
		qreal m_coordinateScaling, m_yOffset, m_xOffset;
	};

}
