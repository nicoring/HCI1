TARGET = QmlOffscreenRenderer
TO_BASE_DIR = ../..

QT *= quick qml

TYPE_DEPENDENCIES += PositionEvents SkeletonTypes

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	QmlOffscreenRenderer.h \
	SceneRenderView.h

SOURCES += \
	QmlOffscreenRenderer.cpp \
	SceneRenderView.cpp

OTHER_FILES += resources/config/QmlOffscreenRenderer.json

RESOURCES += \
	resources/QmlOffscreenRenderer.qrc
