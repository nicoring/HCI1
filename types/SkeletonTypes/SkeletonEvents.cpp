#include "SkeletonEvents.h"


bool mtq::EnhancedSkeletonEvent::selectionAt(const QPoint &point) const
{
	if (dataImage().size().height()>point.y()/imageDownscaleFactor()
		   && dataImage().size().width()>point.x()/imageDownscaleFactor()
		   && point.x() >= 0 && point.y() >= 0) {
		return (bool) (dataImage().pixelIndex(point/imageDownscaleFactor()) & EnhancedSkeletonEvent::ENUM_CHANNELS::SELECTION);
	}
	return false;
}
