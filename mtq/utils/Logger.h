#pragma once

#include <QDebug>

#include "mtq/utils/Singleton.h"

#define MTQ_LOGLEVEL_ERROR   1
#define MTQ_LOGLEVEL_WARNING 2
#define MTQ_LOGLEVEL_INFO	3
#define MTQ_LOGLEVEL_DEBUG   4

#define MTQ_LOGLEVEL_DEFAULT MTQ_LOGLEVEL_INFO

#define MTQ_ERROR	Logger::instance().error(MTQ_TARGET) << "[Error - " << MTQ_TARGET << "]: "
#define MTQ_WARNING	Logger::instance().warning(MTQ_TARGET) << "[Warning - " << MTQ_TARGET << "]: "
#define MTQ_INFO	Logger::instance().info(MTQ_TARGET) << "[Info - " << MTQ_TARGET << "]: "
#define MTQ_DEBUG	Logger::instance().debug(MTQ_TARGET) << "[Debug - " << MTQ_TARGET << "]: "

namespace mtq {

	class MTQ_EXPORT_MTQ Logger {
		MTQ_SINGLETON(Logger)
	public:
		typedef uint Level;

		~Logger();
		void initialize();

		QDebug error(const QString &context);
		QDebug warning(const QString &context);
		QDebug info(const QString &context);
		QDebug debug(const QString &context);

	private:
		Logger();

		QMap<QString, Level> m_logLevels;
		Level m_defaultLogLevel;
		QString m_rubbish;
	};

}
