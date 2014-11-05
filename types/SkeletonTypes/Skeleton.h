#pragma once

#include <QtCore>

#include <mtq/datatypes/Geometry.h>
//#include <mtq/core/PluginRegistry.h>

#include "SkeletonTypes/Bone.h"
#include "SkeletonTypes/SkeletonBoneConnector.h"

namespace mtq {

class MTQ_EXPORT_TYPE Skeleton
{
	public:
		typedef QSharedPointer<Skeleton> Ptr;

		Skeleton(bool initializeWithDefault = false);

		QVector3D rootPosition() const;
		void setRootPosition(QVector3D pos);
		SkeletonBoneConnector::Ptr m_connector;
		QMap<Bone::Type, Bone::Ptr> m_bones;

	private:
		QVector3D m_rootPosition;
		void initializeDefaultBones();
		void initializeEmpty();
};


}
