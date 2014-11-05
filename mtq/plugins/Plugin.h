#pragma once

#include <QtCore>
#include <QThread>

#include "mtq/utils/TypeId.h"
#include "mtq/utils/Configuration.h"

#ifndef STRINGIFY
	#define QUOTE(str) #str
	#define STRINGIFY(str) QUOTE(str)
#endif

#define MTQ_PLUGIN(PluginT) \
	public: \
		typedef QSharedPointer<PluginT> Ptr; \
		PluginT(const QString &pluginName, const Configuration &config); \
		static Plugin* createInstance(const QString &pluginName, const Configuration &config) { return new PluginT(pluginName, config); } \
		static QString staticTypeName() { return STRINGIFY(PluginT); } \
		static TypeId staticTypeId() { return TypeId(&staticMetaObject); }

#define MTQ_REGISTER_PLUGIN(PluginT) \
	bool __registered_##PluginT = mtq::PluginRegistry::instance().registerPluginType(PluginT::staticTypeId(), PluginT::staticTypeName(), &PluginT::createInstance);

namespace mtq {

	class Plugin;

	class WorkerThread : public QThread
	{
		Q_OBJECT
	private:
		WorkerThread(Plugin *parentPlugin);
		void run() Q_DECL_OVERRIDE;

		Plugin *m_parentPlugin;

	friend class Plugin;
	};

	class MTQ_EXPORT_MTQ Plugin : public QObject
	{
		Q_OBJECT
	public:
		typedef QSharedPointer<Plugin> Ptr;

		virtual ~Plugin();

		QString pluginName() const;
		const Configuration config() const;

		void start();
		void stop();
		bool isInitialized();
		bool isRunning();
		bool runsThreaded();

	protected:
		virtual void initialize();
		virtual void run();
		virtual void cleanUp();

	private:
		const QString m_pluginName;

		bool m_isInitialized;
		bool m_isRunning;
		bool m_runsThreaded;

		const Configuration m_config;
		WorkerThread *m_thread;

	friend class WorkerThread;

		MTQ_PLUGIN(Plugin)
	};

}
