#pragma once

#include "QmlLayouter/transformation/LsTransformation.h"

namespace mtq {

	class RigidBodyTransformation : public LsTransformation
	{
	public:
		RigidBodyTransformation(qreal alpha = 1);

	protected:
		qreal calculateMu(QVector2D pStar,
						  QVector2D qStar,
						  QVector<qreal> weights) const;
	};

}
