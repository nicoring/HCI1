TARGET = SkeletonTypes

TO_BASE_DIR = ../..

DEPENDENCIES +=

include($${TO_BASE_DIR}/buildsystem/type.pri)

HEADERS += \
	Bone.h \
	Skeleton.h \
	SkeletonBoneConnector.h \
	SkeletonEvents.h

SOURCES += \
	Bone.cpp \
	Skeleton.cpp \
	SkeletonBoneConnector.cpp \
	SkeletonEvents.cpp
