#pragma once

#include "QmlLayouter/transformation/ControlPointTransformation.h"

namespace mtq {

	class LsTransformation : public ControlPointTransformation
	{
	public:
		LsTransformation(qreal alpha = 1);

		QVector2D transformPoint(const QVector2D &point) const;

	protected:
		virtual qreal calculateMu(QVector2D pStar,
								  QVector2D qStar,
								  QVector<qreal> weights) const = 0;

	private:
		qreal m_alpha;
	};

}
