TARGET = HeadInfoEventProvider

TO_BASE_DIR = ../..

QT += network

DEPENDENCIES += NatNetSDK

TYPE_DEPENDENCIES += PositionEvents SkeletonTypes

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	HeadInfoEventProvider.h

SOURCES += \
	HeadInfoEventProvider.cpp

OTHER_FILES +=

RESOURCES +=
