TARGET = DebugView

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

QT += quick gui core opengl 3d

DEPENDENCIES += Boost OSG

TYPE_DEPENDENCIES = SkeletonTypes

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	ShadowViewerWidget.h \
	DebugView.h \
	ShadowViewerWorker.h

SOURCES += \
	ShadowViewerWidget.cpp \
	DebugView.cpp \
	ShadowViewerWorker.cpp

RESOURCES += \
	resources/DebugView.qrc

OTHER_FILES += \
	qml/BasicNormalizedShaderView.qml \
	qml/BasicRealWorldShaderView.qml \
	qml/FootReachabilityView.qml \
	qml/HandReachabilityView.qml \
	qml/LegibilityView.qml \
	qml/ShadowView.qml \
	qml/Slider.qml \
	qml/VisibilityView.qml \
	qml/WalkingDistanceView.qml \
	qml/MixedViewVisibility.qml \
	qml/MixedViewReachability.qml \
	qml/ParquetBackground.qml \
	qml/ReachVisMixShader.qml \
	qml/Selecting.qml \
	resources/config/DebugView.json \
	qml/ReachVisMixShader.qml
