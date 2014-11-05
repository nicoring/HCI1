#include "LsTransformation.h"

#include <cmath>

#include <mtq/utils/Logger.h>

using namespace mtq;

LsTransformation::LsTransformation(qreal alpha)
	: m_alpha(alpha)
{
}

QVector2D LsTransformation::transformPoint(const QVector2D &point) const
{
	if(m_srcPoints.length() != m_destPoints.length()) {
		MTQ_WARNING << "transformPoint() was called" <<
					   "but there are more source than destination points, " <<
					   "or the other way around";
		return point;
	}
	int numPoints = m_srcPoints.length();
	if(numPoints < 2)
		return point;

	QVector2D pWeighted, qWeighted; // = swp, swq

	QVector<qreal> weights(numPoints);
	qreal weightSum = 0;

	for(int i=0; i<numPoints; i++) {

		/*
		 * if ((i==oldDotL[k].x) && j==oldDotL[k].y)
		 *   break;
		 * //w[k] = pow((i-oldDotL[k].x)*(i-oldDotL[k].x) + (j-oldDotL[k].y)*(j-oldDotL[k].y), -alpha);
		 * w[k] = 1/((i-oldDotL[k].x)*(i-oldDotL[k].x) + (j-oldDotL[k].y)*(j-oldDotL[k].y));
		 * sw = sw + w[k];
		 * swp = swp + w[k] * oldDotL[k];
		 * swq = swq + w[k] * newDotL[k];
		 */
		QVector2D p = m_srcPoints.at(i);
		QVector2D q = m_destPoints.at(i);

		if (point == p)
			return q;

		//equation (2), think harder
		qreal w = std::pow((point - p).lengthSquared(), -m_alpha);
		weights[i] = w;
		weightSum += w;

		pWeighted += w * p;
		qWeighted += w * q;
	}

	/*
	 * pstar = (1 / sw) * swp ;
	 * qstar = 1/sw * swq;
	 */
	QVector2D pStar = 1 / weightSum * pWeighted; // = pstar
	QVector2D qStar = 1 / weightSum * qWeighted; // = qstar

	//ALGORITHM SPECIFIC CODE
	qreal mu = calculateMu(pStar, qStar, weights); // = miu_r or miu_s

	//GENERIC CODE
	QVector2D temp, newPoint;

	QVector2D cur = point - pStar;
	QVector2D curT = QVector2D(-cur.y(), cur.x());

	for(int i=0; i<numPoints; i++) {
		QVector2D p = m_srcPoints.at(i);
		QVector2D q = m_destPoints.at(i);

		QVector2D pRoof = p - pStar;
		QVector2D pRoofT = QVector2D(-pRoof.y(), pRoof.x());

		temp.setX(QVector2D::dotProduct(pRoof, cur) * q.x() - QVector2D::dotProduct(pRoofT, cur) * q.y());
		temp.setY(-QVector2D::dotProduct(pRoof, curT) * q.x() + QVector2D::dotProduct(pRoofT, curT) * q.y());
		temp *= weights[i] / mu;

		newPoint += temp;
	}

	return newPoint + qStar;
}
