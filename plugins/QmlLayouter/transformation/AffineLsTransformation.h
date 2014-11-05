#pragma once

#include "QmlLayouter/transformation/LsTransformation.h"

namespace mtq {

	class AffineLsTransformation : public LsTransformation
	{
	public:
		AffineLsTransformation(qreal alpha = 1);

	protected:
		qreal calculateMu(QVector2D pStar, QVector2D,
						  QVector<qreal> weights) const;
	};

}
