#pragma once

#include <QObject>
#include <QQmlEngine>

namespace mtq {

	class QmlMtqSingelton : public QObject
	{
		Q_OBJECT

	public:
		explicit QmlMtqSingelton(QObject *parent = 0);
	};

	static QObject *mtq_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
	{
		Q_UNUSED(engine)
		Q_UNUSED(scriptEngine)

		return new QmlMtqSingelton();
	}

}
