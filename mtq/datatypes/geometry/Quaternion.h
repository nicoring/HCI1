#pragma once

#include <QQuaternion>

#include "QVector3D.h"

namespace mtq {

	class MTQ_EXPORT_MTQ Quaternion : public QQuaternion
	{
	public:
		Quaternion();
		Quaternion(const QQuaternion &quaternion);
		Quaternion(float scalar, float xpos, float ypos, float zpos);
		Quaternion(float scalar, const QVector3D &vector);
		Quaternion(const QVector4D &vector);

		static Quaternion between(const QVector3D &v1, const QVector3D &v2);
	};
}
