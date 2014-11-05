#include "ColorCapture.h"

#include <mtq/utils/Logger.h>

#include "AlvarTracking/AlvarTracking.h"

using namespace mtq;

ColorCapture::ColorCapture(const Configuration config)
	: Capture(config),
	  cv::VideoCapture()
{
	QList<QVariant> deviceIds = config["cameraDevideIds"].toList();

	foreach(QVariant deviceId, deviceIds) {
		int id = deviceId.toInt();
		MTQ_DEBUG << "Trying to open camera device with id " << id << ".";
		if (open(id)) {
			MTQ_INFO << "Opened camera device with id " << id << ".";
			set(CV_CAP_PROP_FPS, 30);
			set(CV_CAP_PROP_FRAME_WIDTH, 1280);
			set(CV_CAP_PROP_FRAME_HEIGHT, 720);
			return;
		}
	}

	MTQ_WARNING << "Could not open any camera device.";
}

ColorCapture::~ColorCapture()
{
	if (isOpened())
		release();
}

bool ColorCapture::read(cv::Mat & image)
{
	if (!isOpened() || !grab() || !retrieve(image)) {
		MTQ_WARNING << "Could not grab frame.";
		return false;
	}

	cv::cvtColor(image, image, CV_BGR2RGB);
	return true;
}
