#include "AffineLsTransformation.h"

#include <cmath>

#include <mtq/utils/Logger.h>

using namespace mtq;

AffineLsTransformation::AffineLsTransformation(qreal alpha)
	: LsTransformation(alpha)
{
}

qreal AffineLsTransformation::calculateMu(QVector2D pStar, QVector2D,
										  QVector<qreal> weights) const
{
	qreal mu = 0;
	for(int i = 0; i < weights.length(); i++) {
		QVector2D p = m_srcPoints.at(i);
		QVector2D pRoof = p - pStar;
		mu += weights[i] * QVector2D::dotProduct(pRoof, pRoof);
	}
	return mu;
}
