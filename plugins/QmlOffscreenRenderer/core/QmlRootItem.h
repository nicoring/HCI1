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

	public:
		QmlRootItem(QQuickItem *parent = NULL);

		QVariant localConfig() const;
		QVariant globalConfig() const;
		QString name() const;
		QString currentDirectory() const;
		void setName(const QString name);

	signals:
		void ready();

	private:
		QString m_name;
		Configuration m_globalConfig;
		Configuration m_localConfig;
	};
}
