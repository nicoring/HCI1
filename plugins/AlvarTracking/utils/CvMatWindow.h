#pragma once

#include <QtWidgets/QLabel>
#include <opencv2/core/core.hpp>

namespace mtq {

	/**
	 * @brief compatibility CvMatWindow replacement
	 *
	 *Replacement for CvMatWindow (using OpenCV's implementation caused problems in combination with QWindows.
	 */

	class CvMatWindow : public QLabel
	{
		Q_OBJECT
	public:
		explicit CvMatWindow(QWidget *parent = 0);
		void showCvMat(cv::Mat img);

	public slots:
		void hide();

	private slots:
		void doRefresh();
		void doHide();

	signals:
		void needsRefresh();
		void needsHide();
	};

}
