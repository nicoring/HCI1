#include "PolygonUtilities.h"

#include <QMap>

using namespace mtq;

QPolygonF PolygonUtilities::scalePolygon(const qreal scaleFactor, const QPolygonF &polygon)
{
	QPointF center = QPointF(0, 0);
	foreach(QPointF eachPoint, polygon)
		center += eachPoint;
	center /= polygon.size();
	QPolygonF scaledPolygon;
	foreach(QPointF eachPoint, polygon)
		scaledPolygon << center + scaleFactor*(eachPoint-center);
	return scaledPolygon;
}

QPolygonF PolygonUtilities::convexHull(const QPolygonF &polygon)
{
	if(polygon.size() == 0)
		return QPolygonF();
	QMap<qreal, QMap<qreal, QPointF>> sortedPointsMap;
	foreach(QPointF point, polygon) {
		sortedPointsMap[point.x()].insert(point.y(), point);
	}
	QList<QPointF> sortedPoints;
	foreach(auto innerMap, sortedPointsMap) {
		sortedPoints.append(innerMap.values());
	}


	int k = 0, n = sortedPoints.length();

	QVector<QPointF> hull(2*n);

	//build lower hull
	for(int i = 0; i < n; ++i) {
		while (k >= 2 && cross(hull[k-2], hull[k-1], sortedPoints[i]) <= 0)
			k--;
		hull[k++] = sortedPoints[i];
	}

	//build upper hull
	for(int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(hull[k-2], hull[k-1], sortedPoints[i]) <= 0)
			k--;
		hull[k++] = sortedPoints[i];
	}
	hull.resize(k);

	return QPolygonF(hull);
}

qreal PolygonUtilities::cross(const QPointF &o, const QPointF &a, const QPointF &b)
{
	return (a.x() - o.x()) * (b.y() - o.y()) - (a.y() - o.y()) * (b.x() - o.x());
}
