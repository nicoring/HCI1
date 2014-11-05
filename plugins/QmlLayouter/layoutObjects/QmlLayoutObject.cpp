#include "QmlLayoutObject.h"

#include <mtq/core/EventDispatcher.h>
#include <mtq/datatypes/UsersHolder.h>
#include <mtq/utils/Configuration.h>

#include <SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlLayoutObject)

QmlLayoutObject::QmlLayoutObject(QQuickItem *parent)
	: QQuickItem(parent),
	  m_belongingToUser(NULL),
	  m_selectedByUser(NULL)
{
	setObjectName("LayoutObject");
	MTQ_REGISTER_FOR_EVENT(EnhancedSkeletonEvent,
						   SLOT(setUserInfo(Event::Ptr)));
}

bool QmlLayoutObject::selectForLayouting(const User *user)
{
	bool select = ConfigurationService::instance().global()["selectAll"].toBool()
			|| user==m_belongingToUser;
	if(select) {
		m_untransformedPosition = QVector2D(position());
		m_untransformedCenter = QVector2D(center());
		m_untransformedWidth = width();
		m_untransformedHeight = height();
		m_untransformedRotation = rotation();

		m_selectedByUser = user;
		emit selectedByUserChanged();
	}

	return select;
}

QVector2D QmlLayoutObject::untransformedPosition() const
{
	return m_untransformedPosition;
}

QVector2D QmlLayoutObject::untransformedCenter() const
{
	return m_untransformedCenter;
}

qreal QmlLayoutObject::untransformedWidth() const
{
	return m_untransformedWidth;
}

qreal QmlLayoutObject::untransformedHeight() const
{
	return m_untransformedHeight;
}

qreal QmlLayoutObject::untransformedRotation() const
{
	return m_untransformedRotation;
}

void QmlLayoutObject::setUserInfo(Event::Ptr event)
{
	EnhancedSkeletonEvent::Ptr esEvent = EnhancedSkeletonEvent::fromEvent(event);
	QPoint cp = (center()/esEvent->imageDownscaleFactor()).toPoint();
	if (esEvent->visibilityImage().size().height()>cp.y()
			&& esEvent->visibilityImage().size().width()>cp.x()
			&& cp.x() >= 0 && cp.y() >= 0) {
		m_visibility[esEvent->user()] = esEvent->visibilityImage().pixelIndex(cp)/255.;
		m_reachability[esEvent->user()] = esEvent->reachabilityImage().pixelIndex(cp)/255.;
	} else {
		m_visibility[esEvent->user()] = -1;
		m_reachability[esEvent->user()] = -1;
	}

	if (esEvent->user()==m_debugInfoFor) {
		emit visibilityChanged();
		emit reachabilityChanged();
	}

	if(esEvent->user() == m_belongingToUser)
		if(!esEvent->selectionAt(center().toPoint())) {
			m_belongingToUser = NULL;
			emit belongingToUserChanged();
		}

	if(!m_belongingToUser)
		if(esEvent->selectionAt(center().toPoint())) {
			m_belongingToUser = esEvent->user();
			emit belongingToUserChanged();
		}
}

QString QmlLayoutObject::belongingToUser() const
{
	if(m_belongingToUser)
		return m_belongingToUser->username;
	return "";
}

void QmlLayoutObject::setDebugInfoFor(const QString username)
{
	m_debugInfoFor = UsersHolder::instance().getUserByName(username);
	emit debugInfoForChanged();
	emit visibilityChanged();
	emit reachabilityChanged();
}

QString QmlLayoutObject::debugInfoFor() const
{
	if(m_debugInfoFor)
		return m_debugInfoFor->username;
	return "";
}

qreal QmlLayoutObject::visibilityFor(QString username) const
{
	return m_visibility.value(UsersHolder::instance().getUserByName(username),-1);
}

qreal QmlLayoutObject::reachabilityFor(QString username) const
{
	return m_reachability.value(UsersHolder::instance().getUserByName(username),-1);
}

qreal QmlLayoutObject::visibility() const
{
	return m_visibility.value(m_debugInfoFor,-1);
}

qreal QmlLayoutObject::reachability() const
{
	return m_reachability.value(m_debugInfoFor,-1);
}

void QmlLayoutObject::ensureInBoundingBox()
{
	QPointF absoluteCenter = parentItem()->mapToItem(parentItem()->parentItem()->parentItem(), m_untransformedCenter.toPointF());
	//TODO TODO TODO, assigned to Julia
	qreal newX = (absoluteCenter.x() < 0 ? 0 :
					(absoluteCenter.x() > parentItem()->width() ? parentItem()->width() :
						absoluteCenter.x()));
	qreal newY =  (absoluteCenter.y() < 0 ? 0 :
					(absoluteCenter.y() >  parentItem()->height() ? parentItem()->height() :
						absoluteCenter.y()));
	setCenter(parentItem()->mapFromItem(parentItem()->parentItem()->parentItem(), QPointF(newX, newY)));
}


QString QmlLayoutObject::selectedByUser() const {
	if(m_selectedByUser)
		return m_selectedByUser->username;
	return "";
}

void QmlLayoutObject::deselectForLayouting(const User *user) {
	if (user == m_selectedByUser) {
		m_selectedByUser = NULL;
		emit selectedByUserChanged();
	}
}


void QmlLayoutObject::setCenter(QPointF center)
{
	setX(center.x() - width()/2);
	setY(center.y() - height()/2);
	emit centerChanged();
	emit centerXChanged();
	emit centerYChanged();
}

QPointF QmlLayoutObject::center() const
{
	return mapToItem(parentItem(),
					 QPointF(width()/2,height()/2));
}

void QmlLayoutObject::setCenterX(qreal x)
{
	setX(x - width()/2);
	emit centerXChanged();
	emit centerChanged();
}

void QmlLayoutObject::setCenterY(qreal y)
{
	setY(y - height()/2);
	emit centerYChanged();
	emit centerChanged();
}

qreal QmlLayoutObject::centerX()
{
	return mapToItem(parentItem(),
					 QPointF(width()/2,height()/2)).x();
}

qreal QmlLayoutObject::centerY()
{
	return mapToItem(parentItem(),
					 QPointF(width()/2,height()/2)).y();
}

void QmlLayoutObject::setWidthCentered(qreal width)
{
	QPointF centerToPreserve = center();
	setWidth(width);
	setCenter(centerToPreserve);
	emit widthChanged();
}

void QmlLayoutObject::setHeightCentered(qreal height)
{
	QPointF centerToPreserve = center();
	setHeight(height);
	setCenter(centerToPreserve);
	emit heightChanged();
}

