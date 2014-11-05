#include "UserLayouter.h"

#include <cmath>
#include <QtMath>

#include <mtq/utils/Logger.h>

#include "QmlLayouter/transformation/AffineLsTransformation.h"

using namespace mtq;

UserLayouter::UserLayouter(User *user, QQuickItem *qmlUserItem)
	: m_user(user),
	  m_transformation(new AffineLsTransformation()),
	  m_isLayouting(false),
	  m_unusedSkeletonAvailable(false)
{
	m_sourcePolygonViewer = qmlUserItem->findChild<QQuickItem*>("sourcePolygonViewer");
	m_destinationPolygonViewer = qmlUserItem->findChild<QQuickItem*>("destinationPolygonViewer");
	m_transformationViewer = qmlUserItem->findChild<QmlTransformationViewer*>("transformationViewer");
}

UserLayouter::~UserLayouter()
{
	delete m_transformation;
}

void UserLayouter::startLayouting(QSet<QmlLayoutObject *> layoutObjects)
{
	if(m_isLayouting)
		return;
	m_layoutObjects = layoutObjects;
	m_isStarting = true;
	m_isLayouting = true;
}

void UserLayouter::stopLayouting()
{
	updatePolygonViewer(m_sourcePolygonViewer, QPolygonF());

	if(m_transformationViewer)
		m_transformationViewer->setTransformation(NULL);

	m_isLayouting = false;
}

void UserLayouter::updateSkeleton(EnhancedSkeletonEvent::Ptr esEvent)
{
	updatePolygonViewer(m_destinationPolygonViewer, esEvent->workingArea());

	if(!m_isLayouting)
		return;

	m_newestSkeleton = esEvent;
	m_unusedSkeletonAvailable = true;
}

QSet<QmlLayoutObject *> UserLayouter::relayout()
{
	if(!m_isLayouting)
		return QSet<QmlLayoutObject *>();

	m_unusedSkeletonAvailable = false;

	if(m_isStarting) {
		m_isStarting = false;
		m_transformation->setSourcePoints(m_newestSkeleton->workingArea());
		updatePolygonViewer(m_sourcePolygonViewer, m_newestSkeleton->workingArea());
		return QSet<QmlLayoutObject *>();
	}
	m_transformation->setDestinationPoints(m_newestSkeleton->workingArea());

	if(m_transformationViewer)
		m_transformationViewer->setTransformation(m_transformation);

	foreach(QmlLayoutObject *layoutObject, m_layoutObjects) {
		QVector2D untransformedCenter = layoutObject->untransformedCenter();
		QVector2D transformedCenter = m_transformation->transformPoint(untransformedCenter);
		QVector2D untransformedBR = untransformedCenter + QVector2D(10, 10);
		QVector2D transformedBR = m_transformation->transformPoint(untransformedBR);
		QVector2D untransformedVector = untransformedBR - untransformedCenter;
		QVector2D transformedVector = transformedBR - transformedCenter;
		qreal untransformedLength = untransformedVector.length();
		qreal transformedLength = transformedVector.length();

		qreal deltaRotation =
				std::atan2(transformedVector.y(), transformedVector.x())
				-
				std::atan2(untransformedVector.y(), untransformedVector.x());
		qreal factorSize = transformedLength / untransformedLength;

		qreal minSize = 100;
		qreal maxSize = 800;

		if(factorSize*layoutObject->untransformedWidth() < minSize)
			factorSize = minSize / layoutObject->untransformedWidth();
		if(factorSize*layoutObject->untransformedHeight() < minSize)
			factorSize = minSize / layoutObject->untransformedHeight();

		if(factorSize*layoutObject->untransformedWidth() > maxSize)
			factorSize = maxSize / layoutObject->untransformedWidth();
		if(factorSize*layoutObject->untransformedHeight() > maxSize)
			factorSize = maxSize / layoutObject->untransformedHeight();

		layoutObject->setCenter(transformedCenter.toPointF());
		layoutObject->setWidthCentered(factorSize*layoutObject->untransformedWidth());
		layoutObject->setHeightCentered(factorSize*layoutObject->untransformedHeight());
		layoutObject->setRotation(deltaRotation*180/M_PI + layoutObject->untransformedRotation());
	}
	return m_layoutObjects;
}

bool UserLayouter::isUnusedSkeletonAvailable() const
{
	return m_unusedSkeletonAvailable;
}

void UserLayouter::updatePolygonViewer(QQuickItem* polygonViewer, const QPolygonF polygon) {
	if(!polygonViewer)
		return;
	if(!polygonViewer->isVisible())
		return;

	QVariantList polygonPoints;
	foreach (auto eachItem, polygon) {
		polygonPoints << eachItem;
	}
	polygonViewer->setProperty("polygon", polygonPoints);
}
