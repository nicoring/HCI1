#include "SkeletonBoneConnector.h"

#include <mtq/datatypes/Geometry.h>

#include "SkeletonTypes/Skeleton.h"

using namespace mtq;

SkeletonBoneConnector::SkeletonBoneConnector()
{
}


/*
Bone::Matrix SkeletonBoneConnector::getMatrixSkeleton() const
{
	return Matrix4x4();
}

Bone::Matrix SkeletonBoneConnector::getMatrixGlobal() const
{
	Matrix4x4 mat;
	mat.translate(skeleton->rootPosition());
	return mat;
}*/

Bone::Matrix SkeletonBoneConnector::getMatrixToChild() const
{
	return Matrix4x4();
}

Bone::Quat SkeletonBoneConnector::getRotationGlobal() const
{
	return Quaternion();
}

QVector3D SkeletonBoneConnector::getOriginPositionGlobal() const
{
	return skeleton->rootPosition();
}
