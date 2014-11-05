#include "QmlLayoutScene.h"

#include <cmath>
#include <QtMath>

#include <QList>

#include <mtq/core/EventDispatcher.h>
#include <mtq/datatypes/UsersHolder.h>
#include <mtq/utils/Configuration.h>
#include <SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlLayoutScene)

QmlLayoutScene::QmlLayoutScene(QQuickItem *parent)
	: QQuickItem(parent),
	  m_freeSpaceLayouter(new FreeSpaceLayouter()),
	  m_isSimpleLayouting(false),
	  m_firstBoneSet(false),
	  m_oldOffset(QPointF(0, 0))
{
	m_isSimple = ConfigurationService::instance().global()["useSimpleLayouter"].toBool();
	if(m_isSimple) {
		setTransformOrigin(QQuickItem::TopLeft);
		MTQ_REGISTER_FOR_EVENT(SkeletonSourceUpdateEvent,
							   SLOT(receiveSourceSkeleton(Event::Ptr)));
	} else {
		MTQ_REGISTER_FOR_EVENT(EnhancedSkeletonEvent,
							   SLOT(receiveSkeleton(Event::Ptr)));
	}
}

QmlLayoutScene::~QmlLayoutScene()
{
	delete m_freeSpaceLayouter;
}

void QmlLayoutScene::initializeUsers()
{
	if(m_isSimple)
		return;

	QList<QQuickItem*> qmlUserItems = this->findChildren<QQuickItem*>("User");
	foreach(auto eachQmlUserItem, qmlUserItems) {
		QString userName = eachQmlUserItem->property("userName").toString();
		User *user = UsersHolder::instance().getUserByName(userName);
		if(!user) {
			user = new User(userName);
			UsersHolder::instance().addUser(user);
		}
		m_userLayouters[user] = new UserLayouter(user, eachQmlUserItem);
	}
}

void QmlLayoutScene::setUserLayouting(bool isLayouting, QString userName)
{
	if(m_isSimple) {
		m_isSimpleLayouting = isLayouting;
		if(isLayouting) {
			User* user = UsersHolder::instance().getUserByName(userName);
			QList<QmlLayoutObject *> layoutObjects = findChildren<QmlLayoutObject *>("LayoutObject");
			foreach(QmlLayoutObject *layoutObject, layoutObjects) {
				layoutObject->selectForLayouting(user);
			}
		} else {
			m_firstBoneSet = false;
		}
	} else {
		User* user = UsersHolder::instance().getUserByName(userName);
		if(!user)
			return;

		QList<QmlLayoutObject *> layoutObjects = findChildren<QmlLayoutObject *>("LayoutObject");
		if(isLayouting) {
			QSet<QmlLayoutObject *> userObjects;
			foreach(QmlLayoutObject *layoutObject, layoutObjects) {
				if(layoutObject->selectForLayouting(user))
					userObjects.insert(layoutObject);
			}
			m_userLayouters[user]->startLayouting(userObjects);
			m_layoutingUsers.insert(user);
			setUserFocusing(false, userName);
		}
		else {
			m_userLayouters[user]->stopLayouting();
			m_layoutingUsers.remove(user);
			foreach(QmlLayoutObject *layoutObject, layoutObjects) {
				layoutObject->deselectForLayouting(user);
			}
		}
	}
}

void QmlLayoutScene::setUserFocusing(bool isFocusing, QString userName)
{
	if(m_isSimple) {
		return;
	}

	User* user = UsersHolder::instance().getUserByName(userName);
	if(!user)
		return;
	if(m_layoutingUsers.contains(user))
		isFocusing = false;

	if(isFocusing)
		m_focusingUsers.insert(user);
	else
		m_focusingUsers.remove(user);
	emit focusingUsersChanged();
}

QVariantList QmlLayoutScene::focusingUsers() const
{
	QVariantList userNames;
	foreach(const User* eachUser, m_focusingUsers) {
		userNames.append(eachUser->username);
	}
	return userNames;
}

void QmlLayoutScene::receiveSkeleton(Event::Ptr event)
{
	EnhancedSkeletonEvent::Ptr esEvent = EnhancedSkeletonEvent::fromEvent(event);
	const User *user = esEvent->user();
	bool shouldRelayout = m_userLayouters[user]->isUnusedSkeletonAvailable();
	m_userLayouters[user]->updateSkeleton(esEvent);
	m_skeletonCounter++;
	if(m_skeletonCounter == m_userLayouters.size() || shouldRelayout)
		relayout();
}

void QmlLayoutScene::receiveSourceSkeleton(Event::Ptr event)
{
	if(!m_isSimpleLayouting) {
		return;
	}
	SkeletonSourceUpdateEvent::Ptr sEvent = SkeletonSourceUpdateEvent::fromEvent(event);
	Bone::Ptr rootBone = sEvent->skeleton()->m_bones[Bone::Type::ROOT];
	Quaternion newQuaternion = rootBone->getRelativeRotation();
	QVector3D newPosition = rootBone->getOriginPositionGlobal();
	if(m_firstBoneSet) {
		QVector3D newRotatedVec = newQuaternion.rotatedVector(QVector3D(1, 0, 0));
		QVector3D oldRotatedVec = m_oldQuaternion.rotatedVector(QVector3D(1, 0, 0));
		qreal newRotation = (newRotatedVec.y() >= 0 ? 1 : -1)
				* 180 * std::acos(newRotatedVec.x()) / M_PI;
		qreal oldRotation = (oldRotatedVec.y() >= 0 ? 1 : -1)
				* 180 * std::acos(oldRotatedVec.x()) / M_PI;
		qreal deltaRotation = newRotation - oldRotation;

		QPointF originToUser = m_oldPosition.toPointF() - position();
		qreal cos = std::cos(deltaRotation * M_PI / 180.);
		qreal sin = std::sin(deltaRotation * M_PI / 180.);
		QPointF rotatedOriginToUser = QPointF(cos * originToUser.x() - sin * originToUser.y(),
											  sin * originToUser.x() + cos * originToUser.y());
		qreal deltaScale = newPosition.z() / m_oldPosition.z();
		QPointF newOrigin = newPosition.toPointF() - deltaScale*rotatedOriginToUser;
		setRotation(rotation() + deltaRotation);
		setPosition(newOrigin);
		setScale(scale() * deltaScale);

		QList<QmlLayoutObject *> layoutObjects = findChildren<QmlLayoutObject *>("LayoutObject");
		foreach(QmlLayoutObject *layoutObject, layoutObjects) {
			layoutObject->ensureInBoundingBox();
		}
	}
	m_oldQuaternion = newQuaternion;
	m_oldPosition = newPosition;
	m_firstBoneSet = true;
}

void QmlLayoutScene::relayout()
{
	m_skeletonCounter = 0;
	QList<QSet<QmlLayoutObject *>> relayoutedObjects;
	foreach(auto userLayouter, m_userLayouters.values()) {
		relayoutedObjects.append(userLayouter->relayout());
	}
	m_freeSpaceLayouter->freeSpace(relayoutedObjects, findChildren<QmlLayoutObject *>("LayoutObject"), this);
}
