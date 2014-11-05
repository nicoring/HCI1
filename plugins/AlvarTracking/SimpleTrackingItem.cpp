#include "SimpleTrackingItem.h"

#include <mtq/core/EventDispatcher.h>
#include <PositionEvents/SolowheelEvents.h>

//define IS_DOWN_THRESH 1.5
//define IS_UP_THRESH 2.0
//define HAS_MOVED_THRESH 25.0
//define ANGLE_THRESH_UP (35 * (3.14159265358979/180))
//define ANGLE_THRESH_LOW (25 * (3.14159265358979/180))
//define TAP_DELAY 30
//define SHORTEST_TAP 3
//define THI_HEIGHT_THRESHOLD 0.8

//define IS_DOWN_THRESH 1.5
//define IS_UP_THRESH 2.0
//define HAS_MOVED_THRESH 25.0

using namespace mtq;

SimpleTrackingItem::SimpleTrackingItem(int id, AlvarTracking *tracking)
	: TrackingItem(tracking),
	  m_id(id)
{
}

void SimpleTrackingItem::nextFrame(QMap<int, AlvarMarker::Ptr> &markers)
{
	if (!markers.contains(m_id))
		return;
	//foreach (AlvarMarker::Ptr marker, markers.values()) {
	AlvarMarker::Ptr marker = markers[m_id];
	m_position = QPointF((marker->x()+3)*300,(marker->y()+3)*300);
	qreal rotation = std::atan2(marker->markerCorners().at(3).y - marker->markerCorners().at(0).y,
						   marker->markerCorners().at(3).x - marker->markerCorners().at(0).x);
	MTQ_EMIT(new SolowheelEvent(QVector3D(m_position), rotation));

//	if (!markers.contains(2)) return;
//	AlvarMarker::Ptr marker = markers[2];
//	//history data
//	m_lastIsDown = m_isDown;

//	m_position = m_tracking->getCalibration()->cameraToProjector(*marker);

//	m_hasMoved = pow(m_lastContactPos.x() - m_position.x(), 2)
//			+ pow(m_lastContactPos.y() - m_position.y(), 2) > HAS_MOVED_THRESH;
//	if (m_hasMoved) m_lastContactPos = m_position;

//	double distance = m_tracking->getCalibration()->floorDistanceFromPoint(*marker);
//	m_distanceToFloor = distance;
//	if (m_distanceToFloor < IS_DOWN_THRESH) m_isDown = true;
//	if (m_distanceToFloor > IS_UP_THRESH) m_isDown = false;

//	//rotation:

//	//qDebug() << normalToFloorAngle;

//	//TODO: CLEAN UP AND COMMENT!!!
//	/*cv::Vec3f m_xAxisFloor = m_tracking->projectToFloor(cv::Vec3f(1,0,0)); //TODO: move maybe somewhere else
//	cv::Vec3f footXFloor = m_tracking->projectToFloor(marker->axisX());

//	double rotation = acos(footXFloor.dot(m_xAxisFloor));
//	double sign = footXFloor.cross(m_xAxisFloor).dot(marker->axisZ());
//	rotation = _copysign(rotation, sign);*/
//	//TODO: rotation currently not available. Do the needfull.
//	//fillRingbuffer:

//	//cv::Vec3f normal;

//	//set DebugEvent:
//	//TODO: Debugs are not implemented
// /*   m_debugInfo["distanceToFloor"] = qreal(distance);
//	m_debugInfo["normalToFloorAngle"] =0;
//	m_debugInfo["rotation"] = qreal(rotation);
//	//m_debugInfo["text"] = debugString;
//	m_debugInfo["position"] = m_position;
//	m_debugInfo["id"] = 2;
//	m_debugInfo["deleted"] = false;
//	m_tracking->processDebug(QVariant(m_debugInfo));
//*/
//	ContactInfo *info = new ContactInfo();
//	info->center = m_position;
//	if (!m_lastIsDown && m_isDown) {
//		qDebug() << "down";
//		m_tracking->emitContact(info, Event::ContactDown);
//		m_debugInfo["contactState"] ="contactDown";
//		return;
//	}

//	if (m_lastIsDown && m_isDown && m_hasMoved) {
//		qDebug() << "move";
//		m_tracking->emitContact(info, Event::ContactMove);
//		m_debugInfo["contactState"] = "contactMove";
//		return;
//	}

//	if (m_lastIsDown && !m_isDown) {
//		qDebug() << "up";
//		m_tracking->emitContact(info, Event::ContactUp);
//		m_debugInfo["contactState"] = "contactUp";
//		return;
//	}


}
