TARGET = GravitySpaceAdapter

PLUGIN_DIR = $${PWD}
TO_BASE_DIR = ../..

DEPENDENCIES += GravitySpace Boost OpenCV
BOOST_LIBS = system filesystem thread program_options graph chrono
OPENCV_LIBS = core video highgui imgproc calib3d contrib features2d gpu legacy objdetect ml flann

TYPE_DEPENDENCIES += PositionEvents GravitySpaceTypes

include($${TO_BASE_DIR}/buildsystem/plugin.pri)

HEADERS += \
	GravitySpaceAdapter.h

SOURCES += \
	GravitySpaceAdapter.cpp

OTHER_FILES += \
	resources/config/GravitySpaceAdapter.json

RESOURCES += \
	resources/GravitySpaceAdapter.qrc
