#include "EventDispatcher.h"

#include "mtq/utils/Logger.h"

using namespace mtq;

EventEmitter::EventEmitter(const TypeId &eventTypeId)
	: m_eventTypeId(eventTypeId)
{
}

void EventEmitter::registerEventType(const QObject *object, Event::Slot slot)
{
	if (connect(this, SIGNAL(emitEvent(Event::Ptr)), object, slot))
		MTQ_DEBUG << "Connected events of type Event__" << m_eventTypeId.key() << " to SLOT(" << slot << ").";
	else
		MTQ_WARNING << "Could not connect events of type Event__" << m_eventTypeId.key() << " to SLOT(" << slot << ").";

	emit registeredEventType(object, slot);
}

void EventEmitter::deregisterEventType(const QObject *object, Event::Slot slot)
{
	if (disconnect(SIGNAL(emitEvent(Event::Ptr)), object, slot))
		MTQ_DEBUG << "Disconnected events of type Event__" << m_eventTypeId.key() << " from SLOT(" << slot << ").";
	else
		MTQ_WARNING << "Could not disconnect events of type Event__" << m_eventTypeId.key() << " from SLOT(" << slot << ").";

	emit deregisteredEventType(object, slot);
}

bool EventDispatcher::emitEvent(Event::Ptr event)
{
	if(event.isNull()) {
		MTQ_WARNING << "Could not dispatch NULL event.";
		return false;
	}

	TypeId currentTypeId = event->typeId();

	while(currentTypeId.key()) {
		getOrCreateEmitter(currentTypeId)->emitEvent(event);
		currentTypeId = currentTypeId.parent();
	}

	return true;
}

void EventDispatcher::registerForEvent(const QObject *object, const QString &eventTypeName, const TypeId &eventTypeId, const CreateInstanceMethod &method, Event::Slot slot)
{
	registerEventType(eventTypeName, eventTypeId, method);

	EventEmitter::Ptr emitter = getOrCreateEmitter(eventTypeId);
	if (emitter.isNull())
		MTQ_ERROR << "Could not register for event of type Event_" << eventTypeId.key() << ". Event-emitter not found.";
	else
		emitter->registerEventType(object, slot);
}

void EventDispatcher::deregisterForEvent(const QObject *object, const QString &eventTypeName, const TypeId &eventTypeId, const CreateInstanceMethod &method, Event::Slot slot)
{
	registerEventType(eventTypeName, eventTypeId, method);

	EventEmitter::Ptr emitter = getOrCreateEmitter(eventTypeId);
	if (emitter.isNull())
		MTQ_ERROR << "Could not deregister for event of type Event_" << eventTypeId.key() << ". Event-emitter not found.";
	else
		emitter->deregisterEventType(object, slot);
}

const TypeId EventDispatcher::getEventTypeId(const QString &eventTypeName) const
{
	return m_eventTypeIds.value(eventTypeName, TypeId(0));
}

EventEmitter::Ptr EventDispatcher::getOrCreateEmitter(const TypeId &eventTypeId)
{
	QMutexLocker locker(&m_registerMutex);

	if (!m_eventEmitter.contains(eventTypeId.key()))
		m_eventEmitter.insert(eventTypeId.key(), EventEmitter::Ptr(new EventEmitter(eventTypeId)));

	return m_eventEmitter[eventTypeId.key()];
}

void EventDispatcher::registerEventType(const QString &eventTypeName, const TypeId &eventTypeId, const EventDispatcher::CreateInstanceMethod &method)
{
	QMutexLocker locker(&m_registerMutex);

	if (m_eventTypeIds.contains(eventTypeName)) {
		MTQ_INFO << "Event-type " << eventTypeId.key() << " is already registered.";
	} else {
		m_instanceMethods.insert(eventTypeId.key(), method);
		m_eventTypeIds.insert(eventTypeName, eventTypeId);
		MTQ_INFO << "Registered event-type " << eventTypeId.key() << " as " << eventTypeName << ".";
	}
}

Event *EventDispatcher::createNewEvent(const QString &eventTypeName) const
{
	TypeId eventTypeId = getEventTypeId(eventTypeName);

	if (m_instanceMethods.contains(eventTypeId.key())) {
		return m_instanceMethods[eventTypeId.key()]();
	} else {
		MTQ_WARNING << "Could not create new instance of Event__" << eventTypeId.key() << ". Event-type unknown.";
		return NULL;
	}
}
