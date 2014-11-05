TARGET = AlvarTracking

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

DEPENDENCIES += Alvar OpenCV
OPENCV_LIBS = core video highgui imgproc calib3d

TYPE_DEPENDENCIES += PositionEvents

QT *= widgets

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	capture/Capture.h \
	capture/ColorCapture.h \
	AlvarTracking.h \
	utils/CvMatWindow.h \
	SimpleTrackingItem.h \
	TrackingItem.h \
	AlvarMarker.h

SOURCES += \
	AlvarTracking.cpp \
	capture/Capture.cpp \
	capture/ColorCapture.cpp \
	utils/CvMatWindow.cpp \
	SimpleTrackingItem.cpp \
	TrackingItem.cpp \
	AlvarMarker.cpp

RESOURCES += \
	resources/AlvarTracking.qrc

OTHER_FILES += \
	resources/config/AlvarTracking.json
