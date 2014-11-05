#include "AlvarMarker.h"

using namespace mtq;

int AlvarMarker::TTL = 20;//TODO: load from Config

unsigned long AlvarMarker::id()
{
	return m_id;
}

double AlvarMarker::getDistance()
{
	return 0.0;
}

bool AlvarMarker::isCurrent()
{
	return (m_remainingLifetime == AlvarMarker::TTL);
}

bool AlvarMarker::isAlive()
{
	return (m_remainingLifetime);
}

double AlvarMarker::x()
{
	return m_matrix[12];
}

double AlvarMarker::y()
{
	return m_matrix[13];
}

double AlvarMarker::z()
{
	return m_matrix[14];
}

cv::Vec3f AlvarMarker::axisX()
{
	return cv::Vec3f(m_matrix[0], m_matrix[1], m_matrix[2]);
}

cv::Vec3f AlvarMarker::axisY()
{
	return cv::Vec3f(m_matrix[4], m_matrix[5], m_matrix[6]);
}

cv::Vec3f AlvarMarker::axisZ()
{
	return cv::Vec3f(m_matrix[8], m_matrix[9], m_matrix[10]);
}

double AlvarMarker::edgeLength()
{
	return m_edgeLength;
}

std::vector<alvar::PointDouble> AlvarMarker::markerCorners()
{
	return m_markerCorners;
}

cv::Point2d AlvarMarker::center()
{
	// sum up edges (hopefully 4) and divide by 4
	double x = 0;
	double y = 0;

	for(std::vector<alvar::PointDouble>::size_type i = 0; i < markerCorners().size(); i++)
	{
		x += markerCorners().at(i).x;
		y += markerCorners().at(i).y;
	}

	return cv::Point2d(x * 0.25, y * 0.25);
}

void AlvarMarker::update(alvar::MarkerData markerData)
{
	m_id = markerData.GetId();
	markerData.pose.GetMatrixGL(m_matrix);
	m_markerCorners = markerData.marker_corners_img;
	m_remainingLifetime = AlvarMarker::TTL;
	m_edgeLength = markerData.GetMarkerEdgeLength();
}
