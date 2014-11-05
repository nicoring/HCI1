#pragma once

#include <QMutex>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <SkeletonTypes/Bone.h>
#include <SkeletonTypes/Skeleton.h>

#include "DebugView/ShadowViewerWorker.h"

namespace mtq {

	class ShadowViewerWidget
	{
	public:
		ShadowViewerWidget();
		~ShadowViewerWidget();

		void updateUserPosition(Skeleton::Ptr skeleton);
		void drawShadow();

	private:
		bool m_isWorking;
		QMutex m_isWorkingMutex;
		ShadowViewerWorker *m_worker;

		osg::Vec3 m_userPosition; //!<position in window/osg coordinate system
		osgViewer::ScreenCaptureHandler* m_captureHandler;
		osgViewer::Viewer* m_viewer;
		osg::Group* m_root; //!<part of m_viewer, has reference counting and will be destroyed
		osg::Light* m_pLight; //!<child of m_root, has reference counting and will be destroyed

		const float m_optiTrackXFactor;
		const float m_optiTrackXAdd;
		const float m_optiTrackYAdd;
		const float m_optiTrackYFactor;
		const float m_optiTrackZFactor;
	};

}
