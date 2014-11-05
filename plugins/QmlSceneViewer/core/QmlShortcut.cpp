#include "QmlShortcut.h"

#include <QCoreApplication>

#include <mtq/utils/Logger.h>

using namespace mtq;

MTQ_QML_REGISTER_PLUGIN(QmlShortcut)

QmlShortcut::QmlShortcut(QObject *parent) :
	QObject(parent),
	m_keySequence(),
	m_keypressed(false),
	m_blockRepetitions(false)
{
	qApp->installEventFilter(this);
	m_keyHoldTimer = new QTimer(this);
	m_keyHoldTimer->setSingleShot(true);
	m_keyHoldTimer->setInterval(150);
	connect(m_keyHoldTimer, SIGNAL(timeout()), this, SLOT(passKeyRelease()));
}

QVariant QmlShortcut::key() const
{
	return m_keySequence;
}

/**
 * Hier registrieren um Signale für den Shortcut zu empfangen.
 * @param[in] key QVariant von einer QKeySequence.
 */
void QmlShortcut::setKey(const QVariant key)
{
	QKeySequence newKey = key.value<QKeySequence>();
	if(m_keySequence != newKey) {
		m_keySequence = key.value<QKeySequence>();
		emit keyChanged();
	}
}

void QmlShortcut::setBlockRepetitions(const bool blockRepetitions)
{
	m_blockRepetitions = blockRepetitions;
}

bool QmlShortcut::blockRepetitions() const
{
	return m_blockRepetitions;
}

bool QmlShortcut::eventFilter(QObject *obj, QEvent *e)
{
	if((e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) && !m_keySequence.isEmpty()) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

		// Just mod keys is not enough for a shortcut, block them just by returning.
		if (keyEvent->key() >= Qt::Key_Shift && keyEvent->key() <= Qt::Key_Alt)
			return QObject::eventFilter(obj, e);

		int keyInt = keyEvent->modifiers() + keyEvent->key();

		if(QKeySequence(keyInt) != m_keySequence)
			return QObject::eventFilter(obj, e);

		if(e->type() == QEvent::KeyPress) {
			if(!m_keypressed) {
				m_keypressed = true;
				emit activated();
			}
		} else {
			if(m_keypressed) {
				if(m_blockRepetitions)
					m_keyHoldTimer->start();
				else
					passKeyRelease();
			}
		}
	}
	return QObject::eventFilter(obj, e);
}

void QmlShortcut::passKeyRelease()
{
	m_keypressed = false;
	emit released();
}
