#include "QmlTransformationViewer.h"

#include <mtq/utils/Logger.h>

using namespace mtq;

#include <QPainter>

MTQ_QML_REGISTER_PLUGIN(QmlTransformationViewer)

QmlTransformationViewer::QmlTransformationViewer(QQuickItem *parent)
	: QQuickPaintedItem(parent),
	  m_gridSize(50),
	  m_calculated(false)
{
}

int QmlTransformationViewer::gridSize() const
{
	return m_gridSize;
}

void QmlTransformationViewer::setGridSize(int gridSize)
{
	m_gridSize = gridSize;
}

const ControlPointTransformation* QmlTransformationViewer::transformation() const
{
	return m_transformation;
}

void QmlTransformationViewer::setTransformation(const ControlPointTransformation *transformation)
{
	m_transformation = transformation;
	recalculate();
}

void QmlTransformationViewer::paint(QPainter *painter)
{
	if(!m_calculated)
		recalculate();
	painter->setPen(QPen(QColor("#931f00"), 3));

	foreach(QPolygon line, m_lines) {
		painter->drawPolyline(line);
	}
}

void QmlTransformationViewer::recalculate()
{
	m_lines.clear();

	for(int x = 0; x < width(); x += m_gridSize) {
		QPolygon line;

		for(int y = 0; y < height(); y += m_gridSize) {
			line.append(transformPoint(x,y));
		}

		m_lines.append(line);
	}

	for(int y = 0; y < height(); y += m_gridSize) {
		QPolygon line;

		for(int x = 0; x < width(); x += m_gridSize) {
			line.append(transformPoint(x,y));
		}

		m_lines.append(line);
	}
	m_calculated = true;
	update();
}

QPoint QmlTransformationViewer::transformPoint(int x, int y) {
	if(m_transformation) {
		QPointF mappedToParentPoint = mapToItem(dynamic_cast<QQuickItem*>(parent()),QPoint(x,y));
		QPoint transformedPoint = m_transformation->transformPoint(QVector2D(mappedToParentPoint)).toPoint();

		return mapFromItem(dynamic_cast<QQuickItem*>(parent()),transformedPoint).toPoint();
	} else {
		return QPoint(x,y);
	}
}
