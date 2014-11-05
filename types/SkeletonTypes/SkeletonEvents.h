#pragma once

#include <QImage>
#include <QPolygonF>
#include <mtq/events/Event.h>
#include <mtq/datatypes/User.h>

#include "SkeletonTypes/Skeleton.h"

namespace mtq {

	class MTQ_EXPORT_TYPE SkeletonEvent : public Event
	{
		Q_OBJECT

		MTQ_EVENT(SkeletonEvent)
		MTQ_EVENT_PROPERTY(Skeleton::Ptr, skeleton)

	public:
		SkeletonEvent(QSharedPointer<Skeleton> skele)
		  : Event(),
			m_skeleton(skele)
		{}
	};

	class MTQ_EXPORT_TYPE SkeletonSourceUpdateEvent : public SkeletonEvent
	{
		Q_OBJECT

		MTQ_EVENT(SkeletonSourceUpdateEvent)
		MTQ_EVENT_POINTER_PROPERTY(User*, user)
		MTQ_EVENT_PROPERTY(QString, source)

	public:
		SkeletonSourceUpdateEvent(QSharedPointer<Skeleton> skele,   User* user, QString source)
		  : SkeletonEvent(skele),
			m_source(source),
			m_user(user)
		{}
	};

	class MTQ_EXPORT_TYPE EnhancedSkeletonEvent : public SkeletonEvent
	{
		Q_OBJECT

		MTQ_EVENT(EnhancedSkeletonEvent)
		MTQ_EVENT_PROPERTY(int, version)
		MTQ_EVENT_POINTER_PROPERTY(User*, user)
		// Sven, feel free to rename/change the QImages...
		MTQ_EVENT_PROPERTY(QImage, visibilityImage)
		MTQ_EVENT_PROPERTY(int, imageDownscaleFactor)
		MTQ_EVENT_PROPERTY(QImage, reachabilityImage)
		MTQ_EVENT_PROPERTY(QImage, dataImage)
		MTQ_EVENT_PROPERTY(QPolygonF, workingArea)

		public:
			bool selectionAt(const QPoint &point) const;
			enum ENUM_CHANNELS {WORKING_SET = 128, SELECTION = 1};
	};

	class MTQ_EXPORT_TYPE PrePolygonEnhancedSkeletonEvent : public SkeletonEvent
	{
		Q_OBJECT

		MTQ_EVENT(PrePolygonEnhancedSkeletonEvent)
		MTQ_EVENT_PROPERTY(int, version)
		MTQ_EVENT_POINTER_PROPERTY(User*, user)

		MTQ_EVENT_PROPERTY(QImage, visibilityImage)
		MTQ_EVENT_PROPERTY(QImage, reachabilityImage)
		MTQ_EVENT_PROPERTY(QPolygonF, visibility)
	};
}
