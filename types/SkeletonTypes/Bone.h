#pragma once

#include <QSharedPointer>

#include <mtq/datatypes/Geometry.h>

namespace mtq {

	class MTQ_EXPORT_TYPE Bone
	{
	public:
		typedef Matrix4x4 Matrix;
		typedef Quaternion Quat;
		typedef QSharedPointer<Bone> Ptr;

		enum class Type {
				__NONE = 0,
				ROOT,
				THIGH_LEFT,
				THIGH_RIGHT,
				SHIN_LEFT,
				SHIN_RIGHT,
				TOE_LEFT,
				TOE_RIGHT,
				FOOT_LEFT,
				FOOT_RIGHT,
				SPINE,
				RIBS,
				SHOULDER_LEFT,
				SHOULDER_RIGHT,
				NECK,
				HEAD,
				UPPERARM_LEFT,
				UPPERARM_RIGHT,
				FOREARM_LEFT,
				FOREARM_RIGHT,
				HAND_LEFT,
				HAND_RIGHT,
				__SIZE

		};

		Bone();
		Bone::Bone(Bone::Type type);
		Ptr parent;
		//add iterator to skeleton?
		//children?

		Type type() const;
		void setType(Type type);

	/*	virtual Matrix getMatrixSkeleton() const;
		virtual Matrix getMatrixGlobal() const;*/

		QVector3D getOriginPositionParent() const;
		QVector3D getOriginPositionSkeleton() const;
		virtual QVector3D getOriginPositionGlobal() const;

		Quat getRotationParent() const;
	//	Quat getRotationSkeleton() const;
	//virtual	Quat getRotationGlobal() const;
		Quat getRelativeRotation() const;

		/*Vec3 pointsToParent() const;
		Vec3 pointsToSkeleton() const;*/
		QVector3D pointsToGlobal() const;

		double getLength() const;
		void setLength(const double &length);
		bool isEndpoint() const;

		void setRelativeRotation(const Quat &relativeRotation);
		//void setBaseRotation(const Quat &baseRotation);
		void updatePointsToGlobal(const QVector3D &point);
		void updatePointsToParent(const QVector3D &point);
		//void performCCIK();
		//attraktor in bone? oder als parameter?
		virtual Matrix getMatrixToChild() const;
	protected:

		Matrix getMatrixParent() const;

		Type m_type;
		bool m_isEndpoint;
		//Matrix m_parentMatrix;+
		double m_length;

		Quat m_rotationRelative, m_baseRotation;
	};

}
