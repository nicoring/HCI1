TARGET = FOVCenterOptitrackDirectly

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

QT += network

DEPENDENCIES += NatNetSDK

TYPE_DEPENDENCIES += PositionEvents

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	FOVCenterOptitrackDirectly.h

SOURCES += \
	FOVCenterOptitrackDirectly.cpp

OTHER_FILES +=

RESOURCES +=
