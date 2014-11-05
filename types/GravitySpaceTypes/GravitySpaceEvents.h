#pragma once

#include <QImage>

#include <mtq/events/Event.h>

namespace mtq {

	class MTQ_EXPORT_TYPE GravitySpaceFrameImageEvent : public Event
	{
		Q_OBJECT
	public:
		GravitySpaceFrameImageEvent(const QImage &image)
		  : Event(),
			m_image(image)
		{}

		MTQ_EVENT(GravitySpaceFrameImageEvent)
		MTQ_EVENT_PROPERTY(QImage, image)
	};

}
