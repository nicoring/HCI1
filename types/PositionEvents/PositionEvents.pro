TARGET = PositionEvents

TO_BASE_DIR = ../..

include($${TO_BASE_DIR}/buildsystem/type.pri)

HEADERS += \
	BodyEvents.h \
	FloorEvents.h \
	PointingEvents.h \
	PositionEvents.h \
	PositionEventDispatcher.h \
	SolowheelEvents.h

SOURCES += \
	PositionEvents.cpp \
	PositionEventDispatcher.cpp
