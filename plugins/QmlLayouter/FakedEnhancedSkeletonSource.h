#pragma once

#include <QPolygonF>
#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/User.h>

namespace mtq {

	class FakedEnhancedSkeletonSource : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(FakedEnhancedSkeletonSource, "layout")

		Q_PROPERTY(QString userName READ userName WRITE setUserName)
		Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
		Q_PROPERTY(qreal size READ size WRITE setSize)
		Q_PROPERTY(qreal x READ x WRITE setX)
		Q_PROPERTY(qreal y READ y WRITE setY)

	public:
		FakedEnhancedSkeletonSource(QQuickItem *parent = 0);

		QString userName() const;
		void setUserName(const QString userName);
		qreal rotation() const;
		void setRotation(const qreal rotation);
		qreal size() const;
		void setSize(const qreal size);
		qreal x() const;
		void setX(const qreal x);
		qreal y() const;
		void setY(const qreal y);

		Q_INVOKABLE void emitCurrent();

	private:
		void calculatePolygon();

		int m_version;
		QString m_userName;
		User* m_user;
		QPolygonF m_basicForm;
		qreal m_size;
		qreal m_rotation;
		qreal m_x;
		qreal m_y;
		QPolygonF m_polygon;
	};

}
