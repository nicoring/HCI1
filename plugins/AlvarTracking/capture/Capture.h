#pragma once

#include <opencv2/opencv.hpp>
#include <QSharedPointer>

#include <mtq/utils/Configuration.h>

namespace mtq {

	/*!
	 * \brief Delivers videos in expected formats
	 */

	class Capture
	{
	public:
		typedef QSharedPointer<Capture> Ptr;

		Capture(const Configuration config);
		virtual ~Capture();

		const Configuration config() const;
		virtual bool read(cv::Mat & image) = 0;

	private:
		Configuration m_config;
	};

}
