#include "QmlTappingUpperBun.h"

#include <mtq/core/EventDispatcher.h>
#include <PositionEvents/FloorEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlTappingUpperBun)

QmlTappingUpperBun::QmlTappingUpperBun(QQuickItem *parent)
	: QQuickItem(parent),
	  PositionEventDispatcher()
{
}

QVector2D QmlTappingUpperBun::lastDocPosition() const
{
	return m_lastDocPosition;
}

void QmlTappingUpperBun::setLastDocPosition(QVector2D position)
{
	m_lastDocPosition = position;
}

bool QmlTappingUpperBun::dragNDropActive() const
{
	return m_dragNDropActive;
}

void QmlTappingUpperBun::setDragNDropActive(bool active)
{
	m_dragNDropActive = active;
	emit dragNDropActiveChanged();
}

bool QmlTappingUpperBun::pickNDropActive() const
{
	return m_pickNDropActive;
}

void QmlTappingUpperBun::setPickNDropActive(bool active)
{
	m_pickNDropActive = active;
	emit pickNDropActiveChanged();
}

bool QmlTappingUpperBun::pilePickNDropActive() const
{
	return m_pilePickNDropActive;
}

void QmlTappingUpperBun::setPilePickNDropActive(bool active)
{
	m_pilePickNDropActive = active;
	emit pilePickNDropActiveChanged();
}

bool QmlTappingUpperBun::dispatch(PositionEvent::Ptr event)
{
	if(event->typeId() == TapDownEvent::staticTypeId()) {
		if (m_pickNDropActive || m_pilePickNDropActive) {
			return true;
		} else {
			return false;
		}
	}

	if(event->typeId() == TapEvent::staticTypeId()) {
		if(m_pickNDropActive) { //second Tap of tap of pick’n’drop
			moveSelectedDocuments(event->position2D());
			setPickNDropActive(false);
			return true;
		}
		if(m_pilePickNDropActive) {
			moveSelectedDocuments(event->position2D());
			setPilePickNDropActive(false);
			return true;
		}
	}

	if(event->typeId() == DoubleTapEvent::staticTypeId()) {
		setDragNDropActive(false);
		setPickNDropActive(false);

		setPilePickNDropActive(true);

		QPointF mappedPosition = QPointF(event->position2D().x(),event->position2D().y());
		emit selectInRadius(QVector2D(mapFromScene(mappedPosition).x(), mapFromScene(mappedPosition).y()));
		return true;
		//		return false; // documents should receive it too
	}

	if(event->typeId() == ContactMoveEvent::staticTypeId()) {
		if(m_dragNDropActive) {
			contactMoveSelectedDocuments(event->position2D());
			return true;
		}
	}

	if(event->typeId() == TapUpEvent::staticTypeId()) {
		if(m_dragNDropActive) {
			emit deselectChildren();
			setDragNDropActive(false);
			return false;
		}
	}


	return false;
}

//Tap and Double Tap, not contactMove
void QmlTappingUpperBun::moveSelectedDocuments(QVector2D eventPosition) {
	emit moveDocument(QVector2D(mapFromScene(QPointF(eventPosition.x(), eventPosition.y())).x(),
								mapFromScene(QPointF(eventPosition.x(), eventPosition.y())).y()));
}

//Drag’n’Drop contactDown
void QmlTappingUpperBun::contactMoveSelectedDocuments(QVector2D eventPosition) {
	QPointF convertedEventPosition = QPointF(eventPosition.x(), eventPosition.y());
	QVector2D mappedEventPosition = QVector2D(mapFromScene(convertedEventPosition).x(),mapFromScene(convertedEventPosition).y());
	QVector2D distance = mappedEventPosition - lastDocPosition();
	if (distance.lengthSquared() < 10000) {
		emit contactMoveDocument(QVector2D(mapFromScene(QPointF(eventPosition.x(),eventPosition.y())).x(),
			mapFromScene(QPointF(eventPosition.x(),eventPosition.y())).y()));
	}
}
