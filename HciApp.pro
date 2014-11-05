TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
	mtq \
	types/PositionEvents \
	types/GravitySpaceTypes \
        types/SkeletonTypes \
        types/RenderingEvents \
	plugins/GravitySpaceAdapter \
	plugins/QmlLayouter \
	plugins/QmlSceneViewer \
        plugins/Qml3dWidget \
	apps/HciApp
