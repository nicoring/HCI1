#include "QmlDocument.h"

#include <PositionEvents/PointingEvents.h>
#include <PositionEvents/FloorEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlDocument)

QmlDocument::QmlDocument(QQuickItem *parent)
	: QmlLayoutObject(parent),
	  PositionEventDispatcher()
{
	m_selected = false;
}

bool QmlDocument::selected() const
{
	return m_selected;
}

void QmlDocument::setSelected(bool selected)
{
	if(selected != m_selected) {
		m_selected = selected;
		emit selectedChanged();
	}
}

bool QmlDocument::dispatch(PositionEvent::Ptr event)
{
	if(event->typeId() == TapEvent::staticTypeId()) {

		if(!(parentItem()->property("pilePickNDropActive").toBool())) {
			parentItem()->setProperty("pickNDropActive", true);
			parentItem()->setProperty("dragNDropActive", false);
			setSelected(true);
		}
		QPointF mappedPosition = QPointF(event->position2D().x(), event->position2D().y());
		emit tap(QVector2D(parentItem()->mapFromScene(mappedPosition).x(), parentItem()->mapFromScene(mappedPosition).y()));
		return true;
	}

	if(event->typeId() == DoubleTapEvent::staticTypeId()) {
		setSelected(true);
		parentItem()->setProperty("pilePickNDropActive", true);
		QPointF mappedPosition = QPointF(event->position2D().x(), event->position2D().y());
		emit doubleTap(QVector2D(parentItem()->mapFromScene(mappedPosition).x(), parentItem()->mapFromScene(mappedPosition).y()));

		return false; //underlying documents should get this too
	}

	if(event->typeId() == TapDownEvent::staticTypeId()) {
		if(!(parentItem()->property("pilePickNDropActive").toBool())
			&& !(parentItem()->property("pickNDropActive").toBool())) {
			parentItem()->setProperty("dragNDropActive", true);
			setSelected(true);
		}
		QPointF mappedPosition = QPointF(event->position2D().x(), event->position2D().y());
		emit tapDown(QVector2D(parentItem()->mapFromScene(mappedPosition).x(), parentItem()->mapFromScene(mappedPosition).y()));
		return true;
	}

	if(event->typeId() == DwellEvent::staticTypeId()) {
		QPointF mappedPosition = QPointF(event->position2D().x(), event->position2D().y());
		QPointF pos = parentItem()->mapFromScene(mappedPosition);

		emit dwell(QVector2D(parentItem()->mapToItem(this, pos).x(), parentItem()->mapToItem(this, pos).y()));
		return true;
	}

	if(event->typeId() == TapUpEvent::staticTypeId()) {
		emit tapUp();
		return true;
	}

	return false;

}
