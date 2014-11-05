#pragma once

#include <QQuickItem>

#include <QMap>

#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/User.h>
#include <mtq/events/Event.h>
#include "QmlLayouter/UserLayouter.h"
#include "QmlLayouter/FreeSpaceLayouter.h"
#include <QmlLayouter/layoutObjects/QmlLayoutObject.h>

namespace mtq {

	class MTQ_EXPORT_PLUGIN QmlLayoutScene : public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QVariantList focusingUsers READ focusingUsers NOTIFY focusingUsersChanged)

		MTQ_QML_PLUGIN_REGISTRATION(QmlLayoutScene, "layout")

	public:
		explicit QmlLayoutScene(QQuickItem *parent = 0);
		~QmlLayoutScene();

		Q_INVOKABLE void initializeUsers();
		Q_INVOKABLE void setUserLayouting(bool isLayouting, QString userName);
		Q_INVOKABLE void setUserFocusing(bool isFocusing, QString userName);

		QVariantList focusingUsers() const;

	signals:
		void focusingUsersChanged();

	public slots:
		void receiveSkeleton(Event::Ptr event);
		void receiveSourceSkeleton(Event::Ptr event);

	private:
		void relayout();

		QMap<const User*, UserLayouter*> m_userLayouters;
		QSet<const User*> m_focusingUsers;
		QSet<const User*> m_layoutingUsers;
		FreeSpaceLayouter *m_freeSpaceLayouter;

		int m_skeletonCounter;

		bool m_isSimple;
		bool m_isSimpleLayouting;
		bool m_firstBoneSet;
		Quaternion m_oldQuaternion;
		QVector3D m_oldPosition;
		QPointF m_oldOffset;
	};

}
