#include "RigidBodyTransformation.h"

#include <cmath>

#include <mtq/utils/Logger.h>

using namespace mtq;

RigidBodyTransformation::RigidBodyTransformation(qreal alpha)
	: LsTransformation(alpha)
{
}

qreal RigidBodyTransformation::calculateMu(QVector2D pStar, QVector2D qStar, QVector<qreal> weights) const
{
	qreal s1 = 0;
	qreal s2 = 0;
	for(int i = 0; i < weights.length(); i++) {
		QVector2D p = m_srcPoints.at(i);
		QVector2D q = m_destPoints.at(i);

		QVector2D pRoof = p - pStar;
		QVector2D pRoofT = QVector2D(-pRoof.y(), pRoof.x());
		QVector2D qRoof = q - qStar;

		s1 += weights[i] * QVector2D::dotProduct(qRoof, pRoof);
		s2 += weights[i] * QVector2D::dotProduct(qRoof, pRoofT);
	}

	return std::sqrt(s1 * s1 + s2 * s2);
}
