TARGET = QmlLayouter

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

QT *= quick core gui

TYPE_DEPENDENCIES += PositionEvents SkeletonTypes

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	layoutObjects/QmlDocument.h \
	layoutObjects/QmlLayoutObject.h \
	FakedEnhancedSkeletonSource.h \
	FreeSpaceLayouter.h \
	PolygonUtilities.h \
	QmlLayoutScene.h \
	TapsCreatingMouseArea.h \
	UserLayouter.h \
	QmlTransformationViewer.h \
	documentManager/QmlTappingUpperBun.h \
	documentManager/QmlTappingLowerBun.h \
	transformation/RigidBodyTransformation.h \
	transformation/ControlPointTransformation.h \
	transformation/AffineLsTransformation.h \
	transformation/LsTransformation.h

SOURCES += \
	layoutObjects/QmlDocument.cpp \
	layoutObjects/QmlLayoutObject.cpp \
	FakedEnhancedSkeletonSource.cpp \
	FreeSpaceLayouter.cpp \
	PolygonUtilities.cpp \
	QmlLayoutScene.cpp \
	TapsCreatingMouseArea.cpp \
	UserLayouter.cpp \
	QmlTransformationViewer.cpp \
	documentManager/QmlTappingLowerBun.cpp \
	documentManager/QmlTappingUpperBun.cpp \
	transformation/RigidBodyTransformation.cpp \
	transformation/ControlPointTransformation.cpp \
	transformation/AffineLsTransformation.cpp \
	transformation/LsTransformation.cpp

OTHER_FILES += \
	qml/Document.qml \
	qml/DocumentFactory.js \
	qml/DocumentStorage.js \
	qml/User.qml \
	qml/QmlPolygonViewer.qml \
	qml/Circle.qml \
	qml/VideoPlayerControls.qml \
	qml/VideoPlayerStream.qml \
	qml/Line.qml \
	qml/DebugInfoExtender.qml
