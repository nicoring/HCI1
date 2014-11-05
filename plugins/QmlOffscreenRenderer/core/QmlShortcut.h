#pragma once

#include <QQmlComponent>
#include <QKeyEvent>
#include <QTimer>

#include <mtq/core/PluginRegistry.h>

namespace mtq {

	class QmlShortcut : public QObject
	{
		Q_OBJECT

		MTQ_QML_PLUGIN_REGISTRATION(QmlShortcut, "core")

		Q_PROPERTY(QVariant key READ key WRITE setKey NOTIFY keyChanged)
		Q_PROPERTY(bool blockRepetitions READ blockRepetitions WRITE setBlockRepetitions)

	public:
		QmlShortcut(QObject *parent = 0);

		void setKey(const QVariant key);
		QVariant key() const;

		void setBlockRepetitions(const bool blockRepetitions);
		bool blockRepetitions() const;

		bool eventFilter(QObject *obj, QEvent *e);

	public slots:
		void passKeyRelease();

	signals:
		void keyChanged();
		void activated();
		void released();
		void pressedAndHold();

	private:
		QKeySequence m_keySequence;
		bool m_keypressed;
		bool m_blockRepetitions;
		QTimer *m_keyHoldTimer;
	};

}
