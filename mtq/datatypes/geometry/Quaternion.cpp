#include "Quaternion.h"

using namespace mtq;


Quaternion::Quaternion()
	: QQuaternion()
{
}

Quaternion::Quaternion(const QQuaternion &quaternion)
	: QQuaternion(quaternion)
{
}

Quaternion::Quaternion(float scalar, float xpos, float ypos, float zpos)
	: QQuaternion(scalar, xpos, ypos, zpos)
{
}

Quaternion::Quaternion(float scalar, const QVector3D &vector)
	: QQuaternion(scalar, vector)
{
}

Quaternion::Quaternion(const QVector4D &vector)
	: QQuaternion(vector)
{
}

/**
 * @brief gives Quaternion to transform between 2 vectors
 * @param v1 first vector
 * @param v2 second vector
 * @return Quaternion
 *
 * based on http://stackoverflow.com/a/11741520
 */
Quaternion Quaternion::between(const QVector3D &v1, const QVector3D &v2)
{

	float kCosTheta = QVector3D::dotProduct(v1, v2);
	float k = sqrt(v1.lengthSquared() * v2.lengthSquared());

	if (kCosTheta / k == -1)
	{
		// 180 degree rotation around any orthogonal vector

		QVector3D other = (abs(QVector3D::dotProduct(v1, QVector3D(1, 0, 0))) < 1.0) ? QVector3D(1, 0, 0) : QVector3D(0, 1, 0);
		return Quaternion(QQuaternion::fromAxisAndAngle((QVector3D::crossProduct(v1, other).normalized()), 180));
	}

	return Quaternion(kCosTheta + k, QVector3D::crossProduct(v1, v2)).normalized();
}
