#pragma once

#include <QQuickPaintedItem>
#include <QPolygon>

#include <mtq/core/PluginRegistry.h>

#include "QmlLayouter/transformation/ControlPointTransformation.h"

namespace mtq {

	class MTQ_EXPORT_PLUGIN QmlTransformationViewer : public QQuickPaintedItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlTransformationViewer, "layout")

		Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize)
		Q_PROPERTY(const ControlPointTransformation* transformation READ transformation WRITE setTransformation)

	public:
		QmlTransformationViewer(QQuickItem *parent = 0);

		int gridSize() const;
		void setGridSize(int gridSize);

		const ControlPointTransformation* transformation() const;
		void setTransformation(const ControlPointTransformation *transformation);

		void paint(QPainter *painter);

	protected slots:
		void recalculate();

	private:
		QPoint transformPoint(int x, int y);
		bool m_calculated;
		int m_gridSize;
		QList<QPolygon> m_lines;
		const ControlPointTransformation *m_transformation;
	};

}
