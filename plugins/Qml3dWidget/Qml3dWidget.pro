TARGET = Qml3dWidget

QT *= 3dquick 3d quick gui opengl

TO_BASE_DIR = ../..

TYPE_DEPENDENCIES += PositionEvents

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

LIBS += -lwinmm

HEADERS += \
    qml3dwidget.h \
    mtqintegratorwidget.h \
    textdrawer.h \
    simplepainter.h \
    midiinterface.h \
    RtMidi.h

SOURCES += \
    qml3dwidget.cpp \
    mtqintegratorwidget.cpp \
    textdrawer.cpp \
    simplepainter.cpp \
    midiinterface.cpp \
    RtMidi.cpp


