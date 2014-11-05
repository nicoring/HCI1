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
	m_frameTimer.start();
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

int QmlRootItem::frameRate() const
{
	return m_frameRate;
}

int QmlRootItem::frameTime() const
{
	return m_frameTime;
}

int QmlRootItem::renderTime() const
{
	return m_renderTime;
}

void QmlRootItem::setName(const QString name)
{
	m_name = name;
	m_localConfig = m_globalConfig["Plugins"][m_name];
	emit ready();
}

void QmlRootItem::frameStarted()
{
	m_renderTimer.restart();
}

void QmlRootItem::frameFinished()
{
	m_frameRate = 0.9 * m_frameRate + 0.1 * 1000.0 / m_frameTimer.elapsed();
	m_frameTime = 0.9 * m_frameTime + 0.1 * m_frameTimer.elapsed();
	m_renderTime = 0.9 * m_renderTime + 0.1 * m_renderTimer.elapsed();
	m_frameTimer.restart();
}
