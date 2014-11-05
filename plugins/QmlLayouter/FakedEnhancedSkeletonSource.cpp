#include "FakedEnhancedSkeletonSource.h"

#include <cmath>

#include <mtq/core/EventDispatcher.h>
#include <mtq/datatypes/UsersHolder.h>
#include <SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(FakedEnhancedSkeletonSource)

FakedEnhancedSkeletonSource::FakedEnhancedSkeletonSource(QQuickItem *parent)
	: QQuickItem(parent),
	  m_version(0),
	  m_size(1)
{
	m_basicForm << QPointF(0, 0) <<
				   QPointF(1, 0.2) <<
				   QPointF(0.3, 0.8) <<
				   QPointF(0, 1) <<
				   QPointF(-0.3, 0.8) <<
				   QPointF(-1, 0.2);
	calculatePolygon();
}

QString FakedEnhancedSkeletonSource::userName() const
{
	return m_userName;
}

void FakedEnhancedSkeletonSource::setUserName(const QString userName)
{
	m_userName = userName;
	m_user = UsersHolder::instance().getUserByName(m_userName);
	if(!m_user) {
		m_user = new User(userName);
		UsersHolder::instance().addUser(m_user);
	}
}

qreal FakedEnhancedSkeletonSource::rotation() const
{
	return m_rotation;
}

void FakedEnhancedSkeletonSource::setRotation(const qreal rotation)
{
	m_rotation = rotation;
}

qreal FakedEnhancedSkeletonSource::size() const
{
	return m_size;
}

void FakedEnhancedSkeletonSource::setSize(const qreal size)
{
	m_size = size;
}

qreal FakedEnhancedSkeletonSource::x() const
{
	return m_x;
}

void FakedEnhancedSkeletonSource::setX(const qreal x)
{
	m_x = x;
}

qreal FakedEnhancedSkeletonSource::y() const
{
	return m_y;
}

void FakedEnhancedSkeletonSource::setY(const qreal y)
{
	m_y = y;
}

void FakedEnhancedSkeletonSource::emitCurrent()
{
	calculatePolygon();
	EnhancedSkeletonEvent *esEvent = new EnhancedSkeletonEvent();
	esEvent->version(m_version);
	m_version++;
	esEvent->user(m_user);
	esEvent->workingArea(m_polygon);
	esEvent->skeleton(Skeleton::Ptr(new Skeleton()));
	MTQ_EMIT(esEvent);
}

void FakedEnhancedSkeletonSource::calculatePolygon()
{
	m_polygon.clear();
	foreach(QPointF point, m_basicForm) {
		qreal sin = std::sin(m_rotation);
		qreal cos = std::cos(m_rotation);
		point *= m_size;
		m_polygon << QPointF(m_x + cos*point.x() - sin*point.y(),
							 m_y + sin*point.x() + cos*point.y());
	}

}
