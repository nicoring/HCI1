#include "CvMatWindow.h"

using namespace mtq;

CvMatWindow::CvMatWindow(QWidget *parent) :
	QLabel(parent)
{
	connect(this, SIGNAL(needsRefresh()), this, SLOT(doRefresh()));
	connect(this, SIGNAL(needsHide()), this, SLOT(doHide()));
}

void CvMatWindow::showCvMat(cv::Mat img)
{
	QImage dest= QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
	setPixmap(QPixmap::fromImage(dest));
	emit needsRefresh();
}

void CvMatWindow::hide()
{
	emit needsHide();
}

void CvMatWindow::doRefresh()
{
	repaint();
	QLabel::show();
}

void CvMatWindow::doHide()
{
	QLabel::hide();
}
