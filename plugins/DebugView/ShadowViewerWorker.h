#pragma once

#include <QThread>

namespace mtq {

	class ShadowViewerWidget;

	class ShadowViewerWorker : public QThread
	{
		Q_OBJECT
	public:
		explicit ShadowViewerWorker(ShadowViewerWidget *shadowViewer, QObject *parent = 0);

	protected:
		virtual void run();

	private:
		ShadowViewerWidget *m_shadowViewer;
	};

}
