#pragma once

#include <QQuickItem>

#include <mtq/datatypes/User.h>
#include <mtq/events/Event.h>

#include <mtq/core/PluginRegistry.h>

namespace mtq {

	class QmlLayoutObject : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlLayoutObject, "layout")
		Q_PROPERTY(QString belongingToUser READ belongingToUser NOTIFY belongingToUserChanged)
		Q_PROPERTY(QString selectedByUser READ selectedByUser NOTIFY selectedByUserChanged)
		Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)
		Q_PROPERTY(qreal centerX READ centerX WRITE setCenterX NOTIFY centerXChanged)
		Q_PROPERTY(qreal centerY READ centerY WRITE setCenterY NOTIFY centerYChanged)
		Q_PROPERTY(qreal widthCentered READ width WRITE setWidthCentered NOTIFY widthChanged)
		Q_PROPERTY(qreal heightCentered READ height WRITE setHeightCentered NOTIFY widthChanged)
		Q_PROPERTY(QString debugInfoFor READ debugInfoFor WRITE setDebugInfoFor NOTIFY debugInfoForChanged)
		Q_PROPERTY(qreal visibility READ visibility NOTIFY visibilityChanged)
		Q_PROPERTY(qreal reachability READ reachability NOTIFY reachabilityChanged)

	public:
		explicit QmlLayoutObject(QQuickItem *parent = 0);
		bool selectForLayouting(const User *user);
		void deselectForLayouting(const User *user);
		QVector2D untransformedPosition() const;
		QVector2D untransformedCenter() const;
		qreal untransformedWidth() const;
		qreal untransformedHeight() const;
		qreal untransformedRotation() const;
		QString belongingToUser() const;
		QString selectedByUser() const;
		void setCenter(QPointF center);
		QPointF center() const;
		void setCenterX(qreal x);
		void setCenterY(qreal y);
		qreal centerX();
		qreal centerY();
		void setWidthCentered(qreal width);
		void setHeightCentered(qreal height);
		void setDebugInfoFor(const QString username);
		QString debugInfoFor() const;
		Q_INVOKABLE qreal visibilityFor(QString username) const;
		Q_INVOKABLE qreal reachabilityFor(QString username) const;
		qreal visibility() const;
		qreal reachability() const;
		void ensureInBoundingBox();

	signals:
		void belongingToUserChanged();
		void selectedByUserChanged();
		void centerChanged();
		void centerXChanged();
		void centerYChanged();
		void widthChanged();
		void heightChanged();
		void debugInfoForChanged();
		void visibilityChanged();
		void reachabilityChanged();
		
	public slots:
		void setUserInfo(Event::Ptr event);

	private:
		QVector2D m_untransformedPosition;
		QVector2D m_untransformedCenter;
		qreal m_untransformedWidth;
		qreal m_untransformedHeight;
		qreal m_untransformedRotation;
		const User *m_belongingToUser, *m_selectedByUser; 
		const User *m_debugInfoFor;
		QHash <const User*,qreal> m_visibility, m_reachability;
	};

}
