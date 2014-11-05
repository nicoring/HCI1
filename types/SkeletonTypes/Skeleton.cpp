#include "Skeleton.h"


namespace mtq {

//MTQ_QML_REGISTER_PLUGIN(Skeleton);

Skeleton::Skeleton(bool initializeWithDefault)
{
	//Type similar to CCSkeleton
	//boneMap
	//iterator von bone nach innen
	//root position
	//iterator über reihenfolge?
	//deepcopy
	//m_connector.skeleton = Skeleton::Ptr(this);
	m_rootPosition = QVector3D(0,0,0);
	m_connector = SkeletonBoneConnector::Ptr(new SkeletonBoneConnector());
	m_connector->skeleton = this;
	if (initializeWithDefault)
	{
		initializeDefaultBones();
	} else {
		initializeEmpty();
	}

}


QVector3D Skeleton::rootPosition() const
{
	return m_rootPosition;
}

void Skeleton::setRootPosition(QVector3D pos)
{
	m_rootPosition = pos;
}

void Skeleton::initializeDefaultBones()
{

	Bone * bone;
	bone = new Bone(Bone::Type::ROOT);
	bone->parent = Bone::Ptr(m_connector);
	bone->updatePointsToParent(QVector3D(0, 0, 0));
	m_bones.insert(Bone::Type::ROOT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::THIGH_LEFT);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	bone->updatePointsToParent(QVector3D(110 , -30, -500));
	m_bones.insert(Bone::Type::THIGH_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::THIGH_RIGHT);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	bone->updatePointsToParent(QVector3D(-110, 30, -500));
	m_bones.insert(Bone::Type::THIGH_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHIN_LEFT);
	bone->parent = m_bones.value(Bone::Type::THIGH_LEFT);
	bone->updatePointsToParent(QVector3D(-30, -76, -300));
	m_bones.insert(Bone::Type::SHIN_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHIN_RIGHT);
	bone->parent = m_bones.value(Bone::Type::THIGH_RIGHT);
	bone->updatePointsToParent(QVector3D(30, -76, -300));
	m_bones.insert(Bone::Type::SHIN_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOOT_LEFT);
	bone->parent = m_bones.value(Bone::Type::SHIN_LEFT);
	bone->updatePointsToParent(QVector3D(75, 120, -60));
	m_bones.insert(Bone::Type::FOOT_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOOT_RIGHT);
	bone->parent = m_bones.value(Bone::Type::SHIN_RIGHT);
	bone->updatePointsToParent(QVector3D(-75, 120, -60));
	m_bones.insert(Bone::Type::FOOT_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SPINE);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	bone->updatePointsToParent(QVector3D(-10, -50, 200));
	m_bones.insert(Bone::Type::SPINE, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::RIBS);
	bone->parent = m_bones.value(Bone::Type::SPINE);
	bone->updatePointsToParent(QVector3D(-10, -37, 185));
	m_bones.insert(Bone::Type::RIBS, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHOULDER_LEFT);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	bone->updatePointsToParent(QVector3D(150, -63, 4));
	m_bones.insert(Bone::Type::SHOULDER_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHOULDER_RIGHT);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	bone->updatePointsToParent(QVector3D(-150, 0, -4));
	m_bones.insert(Bone::Type::SHOULDER_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::NECK);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	bone->updatePointsToParent(QVector3D(2.70618, 33.3702, 83.3179));
	m_bones.insert(Bone::Type::NECK, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HEAD);
	bone->parent = m_bones.value(Bone::Type::NECK);
	bone->updatePointsToParent(QVector3D(7.44226, 70.5485, 144.033));
	m_bones.insert(Bone::Type::HEAD, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::UPPERARM_LEFT);
	bone->parent = m_bones.value(Bone::Type::SHOULDER_LEFT);
	bone->updatePointsToParent(QVector3D(297.702, -14.7026, 35.5535));
	m_bones.insert(Bone::Type::UPPERARM_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::UPPERARM_RIGHT);
	bone->parent = m_bones.value(Bone::Type::SHOULDER_RIGHT);
	bone->updatePointsToParent(QVector3D(-247.703, 48.4504, -21.2448));
	m_bones.insert(Bone::Type::UPPERARM_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOREARM_LEFT);
	bone->parent = m_bones.value(Bone::Type::UPPERARM_LEFT);
	bone->updatePointsToParent(QVector3D(186.106, -43.1801, -64.4078));
	m_bones.insert(Bone::Type::FOREARM_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOREARM_RIGHT);
	bone->parent = m_bones.value(Bone::Type::UPPERARM_RIGHT);
	bone->updatePointsToParent(QVector3D(-187.366, 61.1865, -71.6442));
	m_bones.insert(Bone::Type::FOREARM_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HAND_LEFT);
	bone->parent = m_bones.value(Bone::Type::FOREARM_LEFT);
	bone->updatePointsToParent(QVector3D(130.091, -37.0628, 42.0972));
	m_bones.insert(Bone::Type::HAND_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HAND_RIGHT);
	bone->parent = m_bones.value(Bone::Type::FOREARM_RIGHT);
	bone->updatePointsToParent(QVector3D(-140.164, 8.3147, 18.8257));
	m_bones.insert(Bone::Type::HAND_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::TOE_LEFT);
	bone->parent = m_bones.value(Bone::Type::FOOT_LEFT);
	bone->updatePointsToParent(QVector3D(0, 0, 0./*10841*/));
	m_bones.insert(Bone::Type::TOE_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::TOE_RIGHT);
	bone->parent = m_bones.value(Bone::Type::FOOT_RIGHT);
	bone->updatePointsToParent(QVector3D(0, 0, 0));
	m_bones.insert(Bone::Type::TOE_RIGHT, Bone::Ptr(bone));
}

void Skeleton::initializeEmpty()
{

	Bone * bone;
	bone = new Bone(Bone::Type::ROOT);
	bone->parent = Bone::Ptr(m_connector);
	m_bones.insert(Bone::Type::ROOT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::THIGH_LEFT);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	m_bones.insert(Bone::Type::THIGH_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::THIGH_RIGHT);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	m_bones.insert(Bone::Type::THIGH_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHIN_LEFT);
	bone->parent = m_bones.value(Bone::Type::THIGH_LEFT);
	m_bones.insert(Bone::Type::SHIN_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHIN_RIGHT);
	bone->parent = m_bones.value(Bone::Type::THIGH_RIGHT);
	m_bones.insert(Bone::Type::SHIN_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOOT_LEFT);
	bone->parent = m_bones.value(Bone::Type::SHIN_LEFT);
	m_bones.insert(Bone::Type::FOOT_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOOT_RIGHT);
	bone->parent = m_bones.value(Bone::Type::SHIN_RIGHT);
	m_bones.insert(Bone::Type::FOOT_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SPINE);
	bone->parent = m_bones.value(Bone::Type::ROOT);
	m_bones.insert(Bone::Type::SPINE, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::RIBS);
	bone->parent = m_bones.value(Bone::Type::SPINE);
	m_bones.insert(Bone::Type::RIBS, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHOULDER_LEFT);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	m_bones.insert(Bone::Type::SHOULDER_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::SHOULDER_RIGHT);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	m_bones.insert(Bone::Type::SHOULDER_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::NECK);
	bone->parent = m_bones.value(Bone::Type::RIBS);
	m_bones.insert(Bone::Type::NECK, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HEAD);
	bone->parent = m_bones.value(Bone::Type::NECK);
	m_bones.insert(Bone::Type::HEAD, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::UPPERARM_LEFT);
	bone->parent = m_bones.value(Bone::Type::SHOULDER_LEFT);
	m_bones.insert(Bone::Type::UPPERARM_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::UPPERARM_RIGHT);
	bone->parent = m_bones.value(Bone::Type::SHOULDER_RIGHT);
	m_bones.insert(Bone::Type::UPPERARM_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOREARM_LEFT);
	bone->parent = m_bones.value(Bone::Type::UPPERARM_LEFT);
	m_bones.insert(Bone::Type::FOREARM_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::FOREARM_RIGHT);
	bone->parent = m_bones.value(Bone::Type::UPPERARM_RIGHT);
	m_bones.insert(Bone::Type::FOREARM_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HAND_LEFT);
	bone->parent = m_bones.value(Bone::Type::FOREARM_LEFT);
	m_bones.insert(Bone::Type::HAND_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::HAND_RIGHT);
	bone->parent = m_bones.value(Bone::Type::FOREARM_RIGHT);
	m_bones.insert(Bone::Type::HAND_RIGHT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::TOE_LEFT);
	bone->parent = m_bones.value(Bone::Type::FOOT_LEFT);
	m_bones.insert(Bone::Type::TOE_LEFT, Bone::Ptr(bone));

	bone = new Bone(Bone::Type::TOE_RIGHT);
	bone->parent = m_bones.value(Bone::Type::FOOT_RIGHT);
	m_bones.insert(Bone::Type::TOE_RIGHT, Bone::Ptr(bone));
}


}
