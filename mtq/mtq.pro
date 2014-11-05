TARGET = MTQ
TEMPLATE = lib

TO_BASE_DIR=..

QT *= core widgets

DEPENDENCIES += Qt ICU

LIBS += -L../$${CURRENT_CONFIG}/dependencies

include(../buildsystem/common.pri)

DESTDIR = $${OUT_PWD}/../$${CURRENT_CONFIG}

HEADERS  += \
	core/Application.h \
	core/EventDispatcher.h \
	core/PluginRegistry.h \
	datatypes/Geometry.h \
	datatypes/geometry/Matrix4x4.h \
	datatypes/geometry/Quaternion.h \
	datatypes/User.h \
	events/Actions.h \
	events/Event.h \
	plugins/Plugin.h \
	utils/Configuration.h \
	utils/Logger.h \
	utils/Singleton.h \
	utils/TypeId.h \
	datatypes/user/User.h \
	datatypes/UsersHolder.h

SOURCES += \
	core/Application.cpp \
	core/EventDispatcher.cpp \
	core/PluginRegistry.cpp \
	datatypes/geometry/Matrix4x4.cpp \
	datatypes/geometry/Quaternion.cpp \
	datatypes/user/User.cpp \
	events/Events.cpp \
	main.cpp \
	plugins/Plugin.cpp \
	utils/Configuration.cpp \
	utils/Logger.cpp \
	utils/TypeId.cpp \
	datatypes/UsersHolder.cpp

DEFINES += \
	MTQ_EXPORT_MTQ=Q_DECL_EXPORT

RESOURCES += \
	resources/MTQ.qrc

OTHER_FILES += \
	resources/config/MTQ.json \
	resources/config/Plugin.json
