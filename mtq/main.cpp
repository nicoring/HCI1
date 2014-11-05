#include <QDir>

#include "mtq/core/Application.h"

int main(int argc, char **argv)
{
	QDir::setCurrent(MTQ_TARGET);
	mtq::Application app(argc, argv);
	return app.exec();
}
