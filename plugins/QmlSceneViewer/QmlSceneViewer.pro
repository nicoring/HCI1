TARGET = QmlSceneViewer

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

QT *= quick

TYPE_DEPENDENCIES += PositionEvents RenderingEvents

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	core/QmlPanZoomRootItem.h \
	core/QmlPositionEventProxy.h \
	core/QmlRootItem.h \
	core/QmlShortcut.h \
	QmlSceneViewer.h \
	SceneView.h \
	core/QmlMtqSingelton.h \
	core/QmlEventDummy.h

SOURCES += \
	core/QmlPanZoomRootItem.cpp \
	core/QmlPositionEventProxy.cpp \
	core/QmlRootItem.cpp \
	core/QmlShortcut.cpp \
	QmlSceneViewer.cpp \
	SceneView.cpp \
	core/QmlMtqSingelton.cpp \
	core/QmlEventDummy.cpp

OTHER_FILES += \
	resources/qml/QmlViewerLoader.js \
	resources/qml/QmlViewer.qml \
	resources/config/QmlSceneViewer.json \
	resources/qml/PanZoom.js \
	qml/Factory.js \
	resources/qml/FramerateDisplay.qml

RESOURCES += \
	resources/QmlSceneViewer.qrc
