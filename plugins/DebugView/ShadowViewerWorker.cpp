#include "ShadowViewerWorker.h"

#include "DebugView/ShadowViewerWidget.h"

using namespace mtq;

ShadowViewerWorker::ShadowViewerWorker(ShadowViewerWidget *shadowViewer, QObject *parent)
	: QThread(parent),
	  m_shadowViewer(shadowViewer)
{
}

void ShadowViewerWorker::run()
{
	m_shadowViewer->drawShadow();
}
