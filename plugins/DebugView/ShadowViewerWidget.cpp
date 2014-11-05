#include "ShadowViewerWidget.h"

#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>

using namespace mtq;

ShadowViewerWidget::ShadowViewerWidget()
	: m_worker(new ShadowViewerWorker(this)),
	  m_isWorking(false),

	  m_optiTrackXFactor(10.0),
	  m_optiTrackXAdd(-3.0),
	  m_optiTrackYAdd(0.5),
	  m_optiTrackYFactor(-900.0),
	  m_optiTrackZFactor(0.005),

	  m_root(new osg::Group()),
	  m_pLight(new osg::Light()),
	  m_viewer(new osgViewer::Viewer()),
	  m_captureHandler(
		  new osgViewer::ScreenCaptureHandler(
			  new osgViewer::ScreenCaptureHandler::WriteToFile(
				  "tempCapturedShadowFrame",
				  "jpg",
				  osgViewer::ScreenCaptureHandler::WriteToFile::SavePolicy::OVERWRITE)))
{
	static const float scaleFactor = 0.03333;

	osg::ref_ptr<osgShadow::ShadowedScene> shadowScene = new osgShadow::ShadowedScene;
	osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap;
	shadowScene->setShadowTechnique(sm.get());
	osg::Box* cube = new osg::Box(osg::Vec3(0,0,0), 38.0f*scaleFactor,38.0f*scaleFactor,26.0f*scaleFactor);
	osg::Box* plane = new osg::Box(osg::Vec3(3,0,-0.5),400.0f*scaleFactor,200.0f*scaleFactor,0.5f);
	osg::ShapeDrawable* cubeDrawable = new osg::ShapeDrawable(cube);
	osg::ShapeDrawable* planeDrawable = new osg::ShapeDrawable(plane);
	osg::Geode* cubeGeode = new osg::Geode();
	osg::Geode* planeGeode = new osg::Geode();
	cubeDrawable->setColor(osg::Vec4(0,1,0,1));
	cubeGeode->addDrawable(cubeDrawable);
	planeGeode->addDrawable(planeDrawable);

	shadowScene->addChild(cubeGeode);
	shadowScene->addChild(planeGeode);

	m_pLight->setLightNum(4);
	m_pLight->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pLight->setDirection(osg::Vec3(1, 0, 0));

	// last param	w = 0.0 directional light (direction)
	//			   w = 1.0 point light (position)
	m_pLight->setPosition(osg::Vec4(0, 0, 0, 1.0));
	osg::LightSource* pLightSource = new osg::LightSource;
	pLightSource->setLight(m_pLight);

	shadowScene->addChild(pLightSource);
	m_root->addChild(shadowScene);

	osg::DisplaySettings::instance()->setNumMultiSamples(4);
	m_viewer->setCameraManipulator(new osgGA::TrackballManipulator()); //TODO: only for debugging purposes
	m_viewer->getCameraManipulator()->setHomePosition(osg::Vec3d(4, -2, 170.0 * scaleFactor * 90),
	osg::Vec3d(4, -2, 0), osg::Vec3d(0.0, 1.0, 0.0));

	m_viewer->setUpViewInWindow(0, 0, 700, 700);
	m_viewer->setSceneData(m_root);
	m_viewer->getCamera()->setProjectionMatrixAsOrtho(-7, 7, -7, 7, -8, 8);
	m_viewer->realize();
}

ShadowViewerWidget::~ShadowViewerWidget()
{
	delete m_worker;
	delete m_viewer;
	delete m_captureHandler;
}

void ShadowViewerWidget::updateUserPosition(Skeleton::Ptr skeleton)
{
	m_isWorkingMutex.lock();
	if(!m_isWorking) {
		m_isWorking = true;
		m_isWorkingMutex.unlock();
		m_userPosition = osg::Vec3(skeleton.data()->m_bones.find(Bone::Type::HEAD).value()->getOriginPositionGlobal().x() / (28.0 * m_optiTrackXFactor) + m_optiTrackXAdd,
								   skeleton.data()->m_bones.find(Bone::Type::HEAD).value()->getOriginPositionGlobal().y() / m_optiTrackYFactor + m_optiTrackYAdd,
								   skeleton.data()->m_bones.find(Bone::Type::HEAD).value()->getOriginPositionGlobal().z() * m_optiTrackZFactor);
		m_worker->start();
	} else {
		m_isWorkingMutex.unlock();
	}
}

void ShadowViewerWidget::drawShadow()
{
	m_captureHandler->captureNextFrame(*m_viewer);

	m_pLight->setPosition(osg::Vec4(m_userPosition.x(),m_userPosition.y(),m_userPosition.z(),1.0));

	m_viewer->frame();

	m_isWorkingMutex.lock();
	m_isWorking = false;
	m_isWorkingMutex.unlock();
}
