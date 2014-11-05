#pragma once

#include <QMutex>

#include "mtq/plugins/Plugin.h"
#include "mtq/utils/Configuration.h"
#include "mtq/utils/Logger.h"
#include "mtq/utils/Singleton.h"

#ifndef STRINGIFY
	#define QUOTE(str) #str
	#define STRINGIFY(str) QUOTE(str)
#endif

#define MTQ_QML_PLUGIN_DEFAULT_MAJOR_VERSION 1
#define MTQ_QML_PLUGIN_DEFAULT_MINOR_VERSION 0

#define MTQ_QML_PLUGIN_REGISTRATION_VERSION(QObjectT, ModuleName, MajorVersion, MinorVersion) \
	public: \
		static void registerPlugin() \
		{ \
			qmlRegisterType<QObjectT>("mtq." ModuleName, MajorVersion, MinorVersion, #QObjectT); \
		}

#define MTQ_QML_PLUGIN_REGISTRATION(QObjectT, ModuleName) \
	MTQ_QML_PLUGIN_REGISTRATION_VERSION(QObjectT, ModuleName, MTQ_QML_PLUGIN_DEFAULT_MAJOR_VERSION, MTQ_QML_PLUGIN_DEFAULT_MINOR_VERSION)

#define MTQ_QML_REGISTER_PLUGIN(QObjectT) \
	static bool __registered_##QObjectT = mtq::PluginRegistry::instance().registerQmlPluginType(STRINGIFY(QObjectT), &QObjectT::registerPlugin);

namespace mtq {

	class MTQ_EXPORT_MTQ PluginRegistry
	{
		MTQ_SINGLETON(PluginRegistry)
	public:
		typedef Plugin* (*CreateInstanceMethod)(const QString&, const Configuration&);
		typedef void (*QmlRegisterMethod)();

		PluginRegistry::~PluginRegistry();

		bool registerPluginType(const TypeId &pluginTypeId, const QString &pluginTypeName, const CreateInstanceMethod &method);
		bool registerQmlPluginType(const QString &qmlPluginTypeName, const QmlRegisterMethod &method);
		void loadModules();
		void runAvailableQmlRegistrations();
		void createInstances();

		const TypeId getPluginTypeId(const QString &pluginTypeName) const;

		//TODO remove
		// DEPRECATED
		template <class PluginT>
		QSharedPointer<PluginT> DEPRECATEDgetInstanceByName(QString name)
		{
			return m_namedInstances.value(name, Plugin::Ptr(NULL)).dynamicCast<PluginT>();
		}

	private:
		PluginRegistry();

		void createInstance(const QString &pluginName, const QString &pluginTypeName, const Configuration &config);
		void loadLibraries(const QString &directory);

		QList<Plugin::Ptr> m_instances;
		QMap<TypeId::Key, CreateInstanceMethod> m_instanceMethods;
		QMap<QString, TypeId> m_pluginTypeIds;
		QList<QmlRegisterMethod> m_qmlRegistrations;
		//TODO remove
		QMap<QString, Plugin::Ptr> m_namedInstances;
		Configuration m_config;
		QMutex m_registerMutex, m_instancesMutex;
	};

}
