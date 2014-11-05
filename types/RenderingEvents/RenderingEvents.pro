TARGET = RenderingEvents

QT *= quick gui

TO_BASE_DIR = ../..

include($${TO_BASE_DIR}/buildsystem/type.pri)

HEADERS += \
	SceneViewRenderingDoneEvent.h

SOURCES += \
	RenderingEvents.cpp
