#include "Application.h"

#include <QKeyEvent>
#include <QtCore>
#include <QTime>

#include "mtq/core/EventDispatcher.h"
#include "mtq/core/PluginRegistry.h"
#include "mtq/events/Event.h"
#include "mtq/utils/Configuration.h"
#include "mtq/utils/Logger.h"

using namespace mtq;

Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
	qsrand(QTime::currentTime().msec());
	qRegisterMetaType<Event::Ptr>();
	installEventFilter(this);

	connect(this, SIGNAL(aboutToQuit()), this, SLOT(cleanUp()));

	QString configFile = arguments().count() > 1 ? arguments().at(1) : "";
	ConfigurationService::instance().loadFromFile(configFile);
	Logger::instance().initialize();
	PluginRegistry::instance().loadModules();
	ConfigurationService::instance().loadPluginConfigs();
	PluginRegistry::instance().runAvailableQmlRegistrations();
	PluginRegistry::instance().createInstances();
}

bool Application::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress) {
		switch(((QKeyEvent*)event)->key()) {
		case Qt::Key_Escape:
			quit();
			return true;
		case Qt::Key_F1:
		case Qt::Key_F2:
		case Qt::Key_F3:
		case Qt::Key_F4:
		case Qt::Key_F5:
		case Qt::Key_F6:
		case Qt::Key_F7:
		case Qt::Key_F8:
		case Qt::Key_F9:
		case Qt::Key_F10:
		case Qt::Key_F11:
		case Qt::Key_F12:
			QString key = QString("F%1").arg(((QKeyEvent*)event)->key() - Qt::Key_F1 + 1);
			QVariantMap shortcuts = ConfigurationService::instance().global()["Shortcuts"].toMap();
			if (shortcuts.contains(key))
				MTQ_EMIT(EventDispatcher::instance().createNewEvent(shortcuts[key].toString()))
			else
				MTQ_DEBUG << "No action is assigned to shortcut " << key << ".";
			return true;
		}
	}

	return QObject::eventFilter(obj, event);
}

void Application::cleanUp()
{
	PluginRegistry::instance().~PluginRegistry();
	EventDispatcher::instance().~EventDispatcher();
	ConfigurationService::instance().~ConfigurationService();
	Logger::instance().~Logger();
}

