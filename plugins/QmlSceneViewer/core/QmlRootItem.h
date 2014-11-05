#pragma once

#include <QQuickItem>

#include <mtq/core/PluginRegistry.h>
#include <mtq/utils/Configuration.h>

namespace mtq {

	class QmlRootItem : public QQuickItem
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlRootItem, "core")

		Q_PROPERTY(QString name READ name)
		Q_PROPERTY(QVariant localConfig READ localConfig)
		Q_PROPERTY(QVariant globalConfig READ globalConfig)
		Q_PROPERTY(QString currentDirectory READ currentDirectory)
		Q_PROPERTY(int frameRate READ frameRate)
		Q_PROPERTY(int frameTime READ frameTime)
		Q_PROPERTY(int renderTime READ renderTime)

	public:
		QmlRootItem(QQuickItem *parent = NULL);

		QVariant localConfig() const;
		QVariant globalConfig() const;
		QString name() const;
		QString currentDirectory() const;
		int frameRate() const;
		int frameTime() const;
		int renderTime() const;
		void setName(const QString name);

	public slots:
		void frameStarted();
		void frameFinished();

	signals:
		void ready();

	private:
		QString m_name;
		Configuration m_globalConfig;
		Configuration m_localConfig;
		QElapsedTimer m_frameTimer;
		QElapsedTimer m_renderTimer;
		qreal m_frameRate;
		qreal m_frameTime;
		qreal m_renderTime;
	};
}
