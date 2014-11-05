#include "QmlPanZoomRootItem.h"

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlPanZoomRootItem)

QmlPanZoomRootItem::QmlPanZoomRootItem(QQuickItem *parent) :
	QQuickItem(parent)
{
}

bool QmlPanZoomRootItem::isPanZoomRootItem() const {
	return true;
}
