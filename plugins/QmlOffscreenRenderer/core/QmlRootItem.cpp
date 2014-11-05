#include "QmlRootItem.h"

#include <QDir>

#include <mtq/utils/Logger.h>

#include "QmlSceneViewer/QmlSceneViewer.h"

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlRootItem)

QmlRootItem::QmlRootItem(QQuickItem *parent)
	: QQuickItem(parent),
	  m_globalConfig(ConfigurationService::instance().global())
{
}

QVariant QmlRootItem::localConfig() const
{
	return m_localConfig;
}

QVariant QmlRootItem::globalConfig() const
{
	return m_globalConfig;
}

QString QmlRootItem::name() const
{
	return m_name;
}

QString QmlRootItem::currentDirectory() const
{
	return QDir::currentPath();
}

void QmlRootItem::setName(const QString name)
{
	m_name = name;
	m_localConfig = m_globalConfig["Plugins"][m_name];
	emit ready();
}
