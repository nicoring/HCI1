#include "TrackingItem.h"

#include "AlvarTracking.h"

using namespace mtq;

TrackingItem::TrackingItem(AlvarTracking *tracking)
{
	m_tracking = tracking;
}

void TrackingItem::nextFrame(QMap<int, AlvarMarker::Ptr> &)
{
}
