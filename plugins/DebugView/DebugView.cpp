#include "DebugView.h"

#include <QCoreApplication>

#include <mtq/core/EventDispatcher.h>
#include <SkeletonTypes/SkeletonEvents.h>

using namespace mtq;

MTQ_REGISTER_PLUGIN(DebugView)

DebugView::DebugView(const QString &pluginName, const Configuration &config)
  : Plugin(pluginName, config)
{
	m_shadowViewer = new ShadowViewerWidget();
}
DebugView::~DebugView()
{
	delete m_shadowViewer;
}

void DebugView::initialize()
{
	MTQ_REGISTER_FOR_EVENT(SkeletonEvent,
						   SLOT(handleSkeletonEvent(Event::Ptr)));
}

void DebugView::handleSkeletonEvent(Event::Ptr event)
{
	SkeletonEvent::Ptr sEvent = SkeletonEvent::fromEvent(event);
	m_shadowViewer->updateUserPosition(sEvent->skeleton());
}

