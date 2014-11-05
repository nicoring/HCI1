#pragma once

#include <QMutexLocker>

#define MTQ_SINGLETON(ClassT) \
	public: \
		static ClassT& instance() \
		{ \
			return Singleton<ClassT>::instance(); \
		} \
	friend class Singleton<ClassT>;

namespace mtq {

	template <class ClassT>
	class Singleton
	{
	public:
		static ClassT& instance()
		{
			static QMutex mutex;
			static ClassT *instance;

			if (!instance) {
				QMutexLocker locker(&mutex);
				if (!instance)
					instance = new ClassT();
			}

			return *instance;
		}

		~Singleton()
		{
			if (instance)
				delete instance;
			instance = NULL;
		}

	private:
		Singleton() {}
	};

}
