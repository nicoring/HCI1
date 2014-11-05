#pragma once

#include "AlvarMarker.h"

namespace mtq {

	/**
	 *@brief abstract class for thing with markers that wants to react to marker updates
	 *
	 *A TrackingItem is a thing with one or multiple Markers attached. For each frame, nextFrame() is
	*called to give it the oppertunity to create the necessary Events.
	*/

	class AlvarTracking;

	class TrackingItem
	{
		public:
			TrackingItem(AlvarTracking *tracking);
			virtual void nextFrame(QMap<int, AlvarMarker::Ptr> &markers);

		protected:
			AlvarTracking *m_tracking;

	};

}
