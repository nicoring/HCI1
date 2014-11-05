#pragma once

#include <QList>

#include "mtq/datatypes/User.h"
#include "mtq/utils/Singleton.h"

namespace mtq {

	class MTQ_EXPORT_MTQ UsersHolder
	{
		MTQ_SINGLETON(UsersHolder)

	public:
		~UsersHolder();
		User *getUserByName(QString name);
		void addUser(User *user);
		QList<User *> & users();

	private:
		UsersHolder();
		QList<User*> m_users;

	};

}
