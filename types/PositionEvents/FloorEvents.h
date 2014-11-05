#pragma once

#include <QImage>

#include "PositionEvents/PositionEvents.h"

namespace mtq {

	class MTQ_EXPORT_TYPE FloorEvent : public EnhancedPositionEvent {
		Q_OBJECT
		MTQ_EVENT(FloorEvent)
		MTQ_EVENT_PROPERTY(uint, id)
		MTQ_EVENT_PROPERTY(QImage, image)
		MTQ_EVENT_PROPERTY(float, tiltAngle)
		MTQ_EVENT_PROPERTY(QVector2D, tiltDirection)
		MTQ_EVENT_PROPERTY(QVector2D, tiltMovingDirection)
		MTQ_EVENT_PROPERTY(float, tiltMovingSpeed)
	};

	class MTQ_EXPORT_TYPE ContactDownEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(ContactDownEvent)
	};

	class MTQ_EXPORT_TYPE ContactUpEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(ContactUpEvent)
	};

	class MTQ_EXPORT_TYPE ContactMoveEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(ContactMoveEvent)
	};

	class MTQ_EXPORT_TYPE TapDownEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(TapDownEvent)
	};

	class MTQ_EXPORT_TYPE TapUpEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(TapUpEvent)
	};

	class MTQ_EXPORT_TYPE TapEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(TapEvent)
	};

	class MTQ_EXPORT_TYPE DoubleTapEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(DoubleTapEvent)
	};

	class MTQ_EXPORT_TYPE DwellEvent : public FloorEvent {
		Q_OBJECT
		MTQ_EVENT(DwellEvent)
	};
}
