#pragma once

#include <limits>

#include <QVector2D>

#include <mtq/datatypes/Geometry.h>
#include <mtq/datatypes/User.h>
#include <mtq/events/Event.h>

namespace mtq {

	class MTQ_EXPORT_TYPE PositionEvent : public Event
	{
		Q_OBJECT
	public:
		PositionEvent(const QVector3D position)
		  : Event(),
			m_position(position)
		{}

		QVector2D position2D() const { return m_position.toVector2D(); }

		MTQ_EVENT(PositionEvent)
		MTQ_EVENT_PROPERTY(QVector3D, position)
	};

	class MTQ_EXPORT_TYPE EnhancedPositionEvent : public PositionEvent
	{
		Q_OBJECT
	public:
		EnhancedPositionEvent(const QVector3D &position)
		  : PositionEvent(position),
			m_rotation(std::numeric_limits<qreal>::quiet_NaN()),
			m_size(QSize()),
			m_user(User())
		{}

		EnhancedPositionEvent(const QVector3D &position, const qreal rotation)
		  : PositionEvent(position),
			m_rotation(rotation),
			m_size(QSize()),
			m_user(User())
		{}

		EnhancedPositionEvent(const QVector3D &position, const User &user)
		  : PositionEvent(position),
			m_rotation(std::numeric_limits<qreal>::quiet_NaN()),
			m_size(QSize()),
			m_user(user)
		{}

		EnhancedPositionEvent(const QVector3D &position, const qreal rotation, const User &user)
		  : PositionEvent(position),
			m_rotation(rotation),
			m_size(QSize()),
			m_user(user)
		{}

		EnhancedPositionEvent(const QVector3D &position, const qreal rotation, const QSize &size, const User &user)
		  : PositionEvent(position),
			m_rotation(rotation),
			m_size(size),
			m_user(user)
		{}

		MTQ_EVENT(EnhancedPositionEvent)
		MTQ_EVENT_PROPERTY(qreal, rotation)
		MTQ_EVENT_PROPERTY(QSize, size)
		MTQ_EVENT_PROPERTY(User, user)
	};

}
