#include "PluginRegistry.h"

#include <QDir>
#include <QDirIterator>
#include <QLibrary>
#include <QSharedPointer>

#include "mtq/core/Application.h"
#include "mtq/plugins/Plugin.h"

using namespace mtq;

PluginRegistry::PluginRegistry()
	: m_config(ConfigurationService::instance().global()["PluginRegistry"])
{
}

PluginRegistry::~PluginRegistry()
{
	foreach(Plugin::Ptr plugin, m_instances) {
		plugin->stop();
	}
}

bool PluginRegistry::registerPluginType(const TypeId &pluginTypeId, const QString &pluginTypeName, const CreateInstanceMethod &method)
{
	QMutexLocker locker(&m_registerMutex);

	if (m_pluginTypeIds.contains(pluginTypeName)) {
		MTQ_WARNING << "Plugin-type " << pluginTypeName << " is already registered.";
		return false;
	} else {
		m_instanceMethods.insert(pluginTypeId.key(), method);
		m_pluginTypeIds.insert(pluginTypeName, pluginTypeId);
		MTQ_INFO << "Registered plugin-type " << pluginTypeName << ".";
		return true;
	}
}

bool PluginRegistry::registerQmlPluginType(const QString &qmlPluginTypeName, const PluginRegistry::QmlRegisterMethod &method)
{
	QMutexLocker locker(&m_registerMutex);

	m_qmlRegistrations.append(method);
	MTQ_INFO << "Registered qml-plugin-type " << qmlPluginTypeName << ".";
	return true;
}

void PluginRegistry::loadModules()
{
	registerPluginType(Plugin::staticTypeId(), Plugin::staticTypeName(), &Plugin::createInstance);

	loadLibraries(QDir::currentPath() + QDir::separator() + m_config["typeDir"].toString());
	loadLibraries(QDir::currentPath() + QDir::separator() + m_config["pluginDir"].toString());
}

void PluginRegistry::runAvailableQmlRegistrations()
{
	foreach(QmlRegisterMethod method, m_qmlRegistrations)
		method();
}

void PluginRegistry::createInstances()
{
	QVariantMap plugins = ConfigurationService::instance().global()["Plugins"].toMap();

	foreach(QString pluginName, plugins.keys()) {
		Configuration config = Configuration(plugins[pluginName]);
		QString pluginTypeName = config["pluginType"].toString();
		createInstance(pluginName, pluginTypeName, config);
	}

	foreach(Plugin::Ptr plugin, m_instances) {
		plugin->start();
	}
}

const TypeId PluginRegistry::getPluginTypeId(const QString &pluginTypeName) const
{
	return m_pluginTypeIds.value(pluginTypeName, TypeId(0));
}

void PluginRegistry::createInstance(const QString &pluginName, const QString &pluginTypeName, const Configuration &config)
{
	TypeId pluginTypeId = getPluginTypeId(pluginTypeName);

	if (pluginTypeId.key()) {
		Configuration pluginConfig = config.mergeWith(ConfigurationService::instance().getDefaultConfig(pluginTypeId));
		m_instances.append(Plugin::Ptr(m_instanceMethods[pluginTypeId.key()](pluginName, pluginConfig)));
		m_namedInstances.insert(pluginName, m_instances.last());
		MTQ_INFO << "Created new instance of " << pluginTypeName << " called " << pluginName << ".";
	} else {
		MTQ_WARNING << "Could not create new instance of " << pluginTypeName << ". Plugin-type unknown.";
	}
}

void PluginRegistry::loadLibraries(const QString &directory)
{
	QDirIterator it(directory);

	while (it.hasNext()) {
		QString libraryName = it.next();
		if (libraryName.endsWith('.'))
			continue;

		QLibrary library(libraryName);
		if (library.load())
			MTQ_INFO << "Successfully loaded library " << libraryName << ".";
		else
			MTQ_ERROR << "Failed to load library " << libraryName << ": " << library.errorString() << ".";
	}
}
