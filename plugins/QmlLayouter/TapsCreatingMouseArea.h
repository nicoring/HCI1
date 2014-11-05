#pragma once

#include <QQuickItem>
#include <QTimer>
#include <QVector3D>

#include <mtq/core/PluginRegistry.h>

namespace mtq {

	class TapsCreatingMouseArea : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(TapsCreatingMouseArea, "debug")

	public:
		TapsCreatingMouseArea();

	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void hoverMoveEvent(QHoverEvent * event);

	public slots:
		void disableTap();
		void sendDwellIfPressed();
	private:
		bool m_couldBeTap;
		bool m_couldBeDwell;
		bool m_doubleTap;

		QVector3D m_dwellPosition;

	};

}
