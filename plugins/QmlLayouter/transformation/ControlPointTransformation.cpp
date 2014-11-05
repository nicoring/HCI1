#include "ControlPointTransformation.h"

using namespace mtq;

ControlPointTransformation::ControlPointTransformation()
{

}

void ControlPointTransformation::setSourcePoints(QList<QVector2D> sourcePoints)
{
	m_srcPoints = sourcePoints;
}

void ControlPointTransformation::setSourcePoints(QPolygonF sourcePolygon)
{
	setSourcePoints(polygonToVectorList(sourcePolygon));
}

void ControlPointTransformation::setSourcePoints(QList<QPolygonF> sourcePolygons)
{
	m_srcPoints.clear();
	foreach(QPolygonF polygon, sourcePolygons)
		m_srcPoints.append(polygonToVectorList(polygon));
}

void ControlPointTransformation::setDestinationPoints(QList<QVector2D> destinationPoints)
{
	m_destPoints = destinationPoints;
}

void ControlPointTransformation::setDestinationPoints(QPolygonF destinationPolygon)
{
	setDestinationPoints(polygonToVectorList(destinationPolygon));
}

void ControlPointTransformation::setDestinationPoints(QList<QPolygonF> destinationPolygons)
{
	m_destPoints.clear();
	foreach(QPolygonF polygon, destinationPolygons)
		m_destPoints.append(polygonToVectorList(polygon));
}

QList<QVector2D> ControlPointTransformation::polygonToVectorList(QPolygonF polygon)
{
	QList<QVector2D> list;
	foreach(QPointF point, polygon)
		list << QVector2D(point);
	return list;
}
