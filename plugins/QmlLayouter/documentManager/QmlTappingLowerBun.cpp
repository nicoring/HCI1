#include "QmlTappingLowerBun.h"

#include <PositionEvents/FloorEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlTappingLowerBun)

QmlTappingLowerBun::QmlTappingLowerBun(QQuickItem *parent)
	: QQuickItem(parent),
	  PositionEventDispatcher()
{
}

bool QmlTappingLowerBun::dispatch(PositionEvent::Ptr event)
{
	if(event->typeId() == DoubleTapEvent::staticTypeId()) {
		emit resetStackCounter();
		return true;
	}
	return false;
}
