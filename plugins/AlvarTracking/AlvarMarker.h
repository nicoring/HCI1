#pragma once

#include <Marker.h>
#include <QPointF>
#include <QString>
#include <QSharedPointer>
#include <QVector3D>

namespace mtq {
/**
	 * @brief represents the current state of an AlvarMarker
	 */
	class AlvarMarker
	{
	public:
		typedef QSharedPointer<AlvarMarker> Ptr;

		operator QPointF ()
		{
			return QPointF(x(), y());
		}

		operator cv::Point3f ()
		{
			return cv::Point3f(x(), y(), z());
		}

		operator QVector3D ()
		{
			return QVector3D(x(), y(), z());
		}

		unsigned long id();
		double x();
		double y();
		double z();
		cv::Vec3f axisX();
		cv::Vec3f axisY();
		cv::Vec3f axisZ();
		double edgeLength();
		std::vector<alvar::PointDouble> markerCorners();
		cv::Point2d center();
		void update(alvar::MarkerData markerData);
		virtual void process() {}
		virtual double getDistance();
		//virtual void markerLost() {}
		bool isAlive();
		bool isCurrent();

		int m_remainingLifetime;
		static int TTL;


	protected:
		unsigned long m_id;
		double m_edgeLength;
		double m_matrix[16];
		std::vector<alvar::PointDouble> m_markerCorners;
	};

}
