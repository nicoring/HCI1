#pragma once

#include <QList>
#include <QPolygonF>
#include <QVector2D>

namespace mtq {

	class ControlPointTransformation
	{
	public:
		ControlPointTransformation();

		void setSourcePoints(QList<QVector2D> sourcePoints);
		void setSourcePoints(QPolygonF sourcePolygon);
		void setSourcePoints(QList<QPolygonF> sourcePolygons);
		void setDestinationPoints(QList<QVector2D> destinationPoints);
		void setDestinationPoints(QPolygonF destinationPolygon);
		void setDestinationPoints(QList<QPolygonF> destinationPolygons);

		virtual QVector2D transformPoint(const QVector2D &point) const = 0;

	protected:
		QList<QVector2D> polygonToVectorList(QPolygonF polygon);

		QList<QVector2D> m_srcPoints;
		QList<QVector2D> m_destPoints;
	};

}
