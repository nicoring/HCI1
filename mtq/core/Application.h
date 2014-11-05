#pragma once

#include <qtwidgets/QApplication>

namespace mtq {

	class MTQ_EXPORT_MTQ Application : public QApplication
	{
		Q_OBJECT
	public:
		Application(int &argc, char **argv);

	protected:
		bool eventFilter(QObject *obj, QEvent *event);

	private slots:
		void cleanUp();
	};

}
