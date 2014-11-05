#include "Bone.h"

#include <assert.h>

using namespace mtq;

Bone::Bone()
  : m_baseRotation(),
	m_rotationRelative()
{
}

Bone::Bone(Bone::Type type)
  : m_baseRotation(),
	m_rotationRelative(),
	m_type(type)
{
}

Bone::Matrix Bone::getMatrixToChild() const
{
	Matrix4x4 mat;
	mat.rotate(getRotationParent());
	mat.translate(0,0,getLength());
	//MTQ_DEBUG << getRotationParent();

	return mat;
}

/**
 * @brief Matrix for the bone in the space of it's parent
 * @return Matrix4x4
 *
 * Example: Result transforms a vector parallel to the parent bone to a vector of the same
 * length parallel to this bone.
 *
 */
Bone::Matrix Bone::getMatrixParent() const
{
	if (parent.isNull()) {
		return Bone::Matrix();
	} else {
		return parent->getMatrixToChild();
	}
}

/**
 * @brief Matrix for the bone in the space of the skeleton
 * @return Matrix4x4
 *
 * Example: Result transforms a point in the origin of the skeleton to the origin of this bone.
 *
 */
/*
Bone::Matrix Bone::getMatrixSkeleton() const
{
	if (parent == NULL) {
		return Bone::Matrix();
	} else {
		return  parent->getMatrixSkeleton() * getMatrixParent();
	}
}
*/
/**
 * @brief Matrix for the bone in global space
 * @return Matrix4x4
 *
 * Example: Result transforms  the global origin to the origin of this bone.
 *
 */
/*
Bone::Matrix Bone::getMatrixGlobal() const
{
	//TODO: FIX, something wrong
	assert();
	{
		if (parent == NULL) {
			return Bone::Matrix();
		} else {
			return   getMatrixParent() * parent->getMatrixGlobal();
		}
	}
}
*/


QVector3D Bone::getOriginPositionParent() const
{
	return  getMatrixParent().map(QVector3D(0,0,0));
}

QVector3D Bone::getOriginPositionSkeleton() const
{
	//return  getMatrixSkeleton().map(Vec3(0,0,0));
	if (parent.isNull()) {
		return getOriginPositionParent();
	}
	else {
		return parent->getOriginPositionSkeleton() + getOriginPositionParent();
	}
}

QVector3D Bone::getOriginPositionGlobal() const
{
	return parent->getOriginPositionGlobal() + getOriginPositionParent();
}


Bone::Quat Bone::getRotationParent() const
{
	return (/*m_baseRotation*/m_rotationRelative).normalized();
}

/*
Bone::Quat Bone::getRotationSkeleton() const
{
	//easier way?
	return vec3
}

*/

/*Bone::Quat Bone::getRotationGlobal() const
{
	return parent->getRotationGlobal()*getRotationParent();
}*/




Bone::Quat Bone::getRelativeRotation() const
{
	return m_rotationRelative;
}

QVector3D Bone::pointsToGlobal() const
{
	return getOriginPositionGlobal() + getMatrixToChild().map(QVector3D(0,0,0));
}

double Bone::getLength() const
{
	return m_length;
}

void Bone::setLength(const double &length)
{
	m_length = length;
}

bool Bone::isEndpoint() const
{
	return m_isEndpoint;
}

void Bone::setRelativeRotation(const Bone::Quat &relativeRotation)
{
	m_rotationRelative = relativeRotation.normalized();
}

Bone::Type Bone::type() const
{
	return m_type;
}

void Bone::updatePointsToGlobal(const QVector3D &point)
{
	QVector3D origpos = getOriginPositionGlobal();
	updatePointsToParent(point-origpos);
}

void Bone::updatePointsToParent(const QVector3D &point)
{

	setLength(point.length());
	/*QVector3D test = point;
	test.setY(-test.y());*/
	Quat newRotationSum = Quaternion::between(QVector3D(0,0,1), point);
	//maybe calculate every time asked for instead of store
	m_rotationRelative = ((newRotationSum)/**(-m_baseRotation)*/).normalized();


}

/*
void Bone::setBaseRotation(const Bone::Quat &baseRotation)
{
	m_baseRotation = baseRotation;
}
*/
