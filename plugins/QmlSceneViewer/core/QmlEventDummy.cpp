#include "QmlEventDummy.h"

#include <PositionEvents/FloorEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlEventDummy)

QmlEventDummy::QmlEventDummy(QQuickItem *parent)
	: QQuickItem(parent),
	PositionEventDispatcher()
{
}

bool QmlEventDummy::dispatch(PositionEvent::Ptr event)
{
	if (event->typeId() == TapEvent::staticTypeId()) {
		TapEvent::Ptr tEvent = TapEvent::fromEvent(event);

		QQuickItem *parentItem = dynamic_cast<QQuickItem*>(parent());
		QPointF mappedPosition = QPointF(tEvent->position2D().x(),tEvent->position2D().y());

		emit tap(QVector2D(parentItem->mapFromScene(mappedPosition).x(), parentItem->mapFromScene(mappedPosition).y())/*, tEvent->position2D()*/);
		return true;
	}

	if (event->typeId() == TapDownEvent::staticTypeId()) {
		TapDownEvent::Ptr tEvent = TapDownEvent::fromEvent(event);

		QQuickItem *parentItem = dynamic_cast<QQuickItem*>(parent());
		QPointF mappedPosition = QPointF(tEvent->position2D().x(),tEvent->position2D().y());

		emit tapDown(QVector2D(parentItem->mapFromScene(mappedPosition).x(), parentItem->mapFromScene(mappedPosition).y()));
		return true;
	}

	if (event->typeId() == ContactMoveEvent::staticTypeId()) {
		ContactMoveEvent::Ptr mEvent = ContactMoveEvent::fromEvent(event);

		QQuickItem *parentItem = dynamic_cast<QQuickItem*>(parent());
		QPointF mappedPosition = QPointF(mEvent->position2D().x(),mEvent->position2D().y());

		emit contactMove(QVector2D(parentItem->mapFromScene(mappedPosition).x(), parentItem->mapFromScene(mappedPosition).y()));
		return true;
	}

	if (event->typeId() == TapUpEvent::staticTypeId()) {
		emit tapUp();
	}

	return false;
}
