#pragma once

#include <QList>
#include <QSet>
#include <QString>

#include <mtq/datatypes/User.h>
#include <SkeletonTypes/SkeletonEvents.h>
#include "QmlLayouter/layoutObjects/QmlLayoutObject.h"
#include "QmlLayouter/transformation/ControlPointTransformation.h"
#include "QmlLayouter/QmlTransformationViewer.h"

namespace mtq {

	class UserLayouter
	{
	public:
		UserLayouter(User *user, QQuickItem *qmlUserItem);
		~UserLayouter();
		void startLayouting(QSet<QmlLayoutObject *> layoutObjects);
		void stopLayouting();
		void updateSkeleton(EnhancedSkeletonEvent::Ptr esEvent);
		QSet<QmlLayoutObject *> relayout();
		bool isUnusedSkeletonAvailable() const;

	private:
		void updatePolygonViewer(QQuickItem* polygonViewer, const QPolygonF polygon);

		EnhancedSkeletonEvent::Ptr m_newestSkeleton;
		QSet<QmlLayoutObject *> m_layoutObjects;
		ControlPointTransformation *m_transformation;
		User *m_user;
		bool m_isStarting;
		bool m_isLayouting;
		bool m_unusedSkeletonAvailable;
		QQuickItem *m_sourcePolygonViewer;
		QQuickItem *m_destinationPolygonViewer;
		QmlTransformationViewer *m_transformationViewer;
	};

}
