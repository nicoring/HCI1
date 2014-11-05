#pragma once

#include <QSharedPointer>

#include "SkeletonTypes/Bone.h"

namespace mtq {

	class Skeleton;

	class MTQ_EXPORT_TYPE SkeletonBoneConnector : public mtq::Bone
	{
	public:
		typedef QSharedPointer<SkeletonBoneConnector> Ptr;
		//typedef SkeletonBoneConnector* Ptr;

		SkeletonBoneConnector();

		//virtual Matrix getMatrixParent() const;
		/*virtual Matrix getMatrixSkeleton() const;
		virtual Matrix getMatrixGlobal() const;*/
		virtual Matrix getMatrixToChild() const;
		virtual	Quat getRotationGlobal() const;
		virtual QVector3D getOriginPositionGlobal() const;

		Skeleton* skeleton;
	};

}
