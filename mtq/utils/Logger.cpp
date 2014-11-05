#include "Logger.h"

#include "mtq/utils/Configuration.h"

using namespace mtq;

Logger::Logger()
	: m_defaultLogLevel(MTQ_LOGLEVEL_DEFAULT)
{
}

Logger::~Logger()
{
}

void Logger::initialize()
{
	m_defaultLogLevel = ConfigurationService::instance().global()["Logging"]["defaultLogLevel"].toInt();
	QVariantMap logLevels = ConfigurationService::instance().global()["Logging"]["logLevels"].toMap();

	foreach (QString key, logLevels.keys()) {
		m_logLevels.insert(key, logLevels[key].toInt());
	}
}

QDebug Logger::error(const QString &context)
{
	m_rubbish = "";
	return m_logLevels.value(context, m_defaultLogLevel) >= MTQ_LOGLEVEL_ERROR ? qCritical().nospace() : QDebug(&m_rubbish);
}

QDebug Logger::warning(const QString &context)
{
	m_rubbish = "";
	return m_logLevels.value(context, m_defaultLogLevel) >= MTQ_LOGLEVEL_WARNING ? qWarning().nospace() : QDebug(&m_rubbish);
}

QDebug Logger::info(const QString &context)
{
	m_rubbish = "";
	return m_logLevels.value(context, m_defaultLogLevel) >= MTQ_LOGLEVEL_INFO ? qDebug().nospace() : QDebug(&m_rubbish);
}

QDebug Logger::debug(const QString &context)
{
	m_rubbish = "";
	return m_logLevels.value(context, m_defaultLogLevel) >= MTQ_LOGLEVEL_DEBUG ? qDebug().nospace() : QDebug(&m_rubbish);
}
