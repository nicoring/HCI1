#include "QmlPositionEventProxy.h"

#include <mtq/core/EventDispatcher.h>
#include <PositionEvents/PositionEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlPositionEventProxy)

QmlPositionEventProxy::QmlPositionEventProxy(QQuickItem *parent) :
	QQuickItem(parent),
	m_filterActive(false),
	m_xOffset(0),
	m_yOffset(0),
	m_coordinateScaling(1)
{
	setEnabled(false);
	MTQ_REGISTER_FOR_EVENT(PositionEvent, SLOT(receivePositionEvent(Event::Ptr)));
}

QString QmlPositionEventProxy::eventType() const
{
	return m_eventType;
}

void QmlPositionEventProxy::setEventType(QString typeName)
{
	m_eventType = typeName;
	m_filterActive = !typeName.isEmpty();
	emit eventTypeChanged();
}

qreal QmlPositionEventProxy::xOffset() const
{
	return m_xOffset;
}

void QmlPositionEventProxy::setXOffset(qreal offset)
{
	m_xOffset = offset;
	emit xOffsetChanged();
}

qreal QmlPositionEventProxy::yOffset() const
{
	return m_yOffset;
}

void QmlPositionEventProxy::setYOffset(qreal offset)
{
	m_yOffset = offset;
	emit yOffsetChanged();
}

qreal QmlPositionEventProxy::coordinateScaling() const
{
	return m_coordinateScaling;
}

void QmlPositionEventProxy::setCoordinateScaling(qreal scale)
{
	m_coordinateScaling = scale;
	emit coordinateScalingChanged();
}

void QmlPositionEventProxy::receivePositionEvent(Event::Ptr event) {
	if (!m_filterActive || event->typeName() == m_eventType) {
		PositionEvent::Ptr posEvent = PositionEvent::fromEvent(event);
		this->setX(posEvent->position().x() * m_coordinateScaling + m_xOffset);
		this->setY(posEvent->position().y() * m_coordinateScaling + m_yOffset);
	}
}

