#include "Plugin.h"

#include <QApplication>

#include "mtq/core/PluginRegistry.h"
#include "mtq/utils/Logger.h"

using namespace mtq;

WorkerThread::WorkerThread(Plugin *parentPlugin)
	: m_parentPlugin(parentPlugin)
{
}

void WorkerThread::run()
{
	m_parentPlugin->run();
}

Plugin::Plugin(const QString &pluginName, const Configuration &config)
	: m_pluginName(pluginName),
	  m_config(config),
	  m_isInitialized(false),
	  m_isRunning(false),
	  m_thread(NULL)
{
	m_runsThreaded = m_config["runsThreaded"].toBool();
}

Plugin::~Plugin()
{
	if (m_thread) {
		m_thread->deleteLater();
	}
}

QString Plugin::pluginName() const
{
	return m_pluginName;
}

const Configuration Plugin::config() const
{
	return m_config;
}

void Plugin::start()
{
	if (m_isRunning)
		return;

	if (!isInitialized()) {
		if (runsThreaded()) {
			m_thread = new WorkerThread(this);
			moveToThread(m_thread);
		}
		MTQ_DEBUG << "Initializing plugin " << pluginName() << ".";
		initialize();
		m_isInitialized = true;
	}

	m_isRunning = true;
	MTQ_DEBUG << "Started plugin " << pluginName() << ".";

	if (runsThreaded()) {
		m_thread->start();
	} else {
		run();
	}
}

void Plugin::stop()
{
	if (!isRunning())
		return;

	cleanUp();

	m_isRunning = false;

	MTQ_DEBUG << "Stopped plugin " << pluginName() << ".";

	if (runsThreaded()) {
		m_thread->quit();
		m_thread->wait(1000);
	}
}

bool Plugin::isInitialized()
{
	return m_isInitialized;
}

bool Plugin::isRunning()
{
	return m_isRunning;
}

bool Plugin::runsThreaded()
{
	return m_runsThreaded;
}

void Plugin::initialize()
{
}

void Plugin::run()
{
}

void Plugin::cleanUp()
{
}
