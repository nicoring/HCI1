#pragma once

#include <QtCore>

namespace mtq {

	struct MTQ_EXPORT_MTQ User
	{
		User()
		{}

		User(QString name)
		  : username(name)
		{}

		QString username;
	};

}
