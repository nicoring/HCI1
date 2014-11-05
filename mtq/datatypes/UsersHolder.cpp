#include "UsersHolder.h"

#include "mtq/utils/Configuration.h"

using namespace mtq;

UsersHolder::~UsersHolder()
{
	foreach(User *user, m_users)
		delete user;
}

User *UsersHolder::getUserByName(QString name)
{
	foreach(User *user, m_users)
		if(name == user->username)
			return user;
	return NULL;
}

void UsersHolder::addUser(User *user)
{
	m_users.append(user);
}

QList<User *> &UsersHolder::users()
{
	return m_users;
}

UsersHolder::UsersHolder()
{
	QMap<QString, QVariant> users = ConfigurationService::instance().global()["Users"].toMap();
	foreach(QString user, users.keys()) {
		addUser(new User(user));
	}
}
