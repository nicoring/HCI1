#pragma once

#include <QPolygonF>

namespace mtq {

	class PolygonUtilities
	{
	public:
		static QPolygonF scalePolygon(const qreal scaleFactor, const QPolygonF &polygon);
		static QPolygonF convexHull(const QPolygonF &polygon);
		static qreal cross(const QPointF &o, const QPointF &a, const QPointF &b);
	};

}
