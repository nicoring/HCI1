#pragma once

#include "Capture.h"

namespace mtq {
	/**
	 * @brief captures images from an openCV video source
	 */
	class ColorCapture : public Capture, private cv::VideoCapture
	{
	public:
		ColorCapture(const Configuration config);
		~ColorCapture();

		bool read(cv::Mat & image);
	};

}
