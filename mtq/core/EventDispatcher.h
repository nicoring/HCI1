#pragma once

#include <QObject>
#include <QMap>
#include <QSharedPointer>

#include "mtq/core/Application.h"
#include "mtq/events/Event.h"
#include "mtq/utils/Logger.h"
#include "mtq/utils/Singleton.h"
#include "mtq/utils/TypeId.h"

#define MTQ_EMIT(EventT) \
	mtq::EventDispatcher::instance().emitEvent(Event::Ptr(EventT));

#define MTQ_REGISTER_FOR_EVENT(EventT, Slot) \
	mtq::EventDispatcher::instance().registerForEvent(this, EventT::staticTypeName(), EventT::staticTypeId(), &EventT::createInstance, Slot);

#define MTQ_DEREGISTER_FOR_EVENT(EventT, Slot) \
	mtq::EventDispatcher::instance().deregisterForEvent(this, EventT::staticTypeName(), EventT::staticTypeId(), &EventT::createInstance, Slot);

namespace mtq {

	class EventDispatcher;

	class MTQ_EXPORT_MTQ EventEmitter : public QObject
	{
		Q_OBJECT
	public:
		typedef QSharedPointer<EventEmitter> Ptr;

		explicit EventEmitter(const TypeId &eventTypeId);

	signals:
		void emitEvent(Event::Ptr event);
		void registeredEventType(const QObject *object, Event::Slot slot);
		void deregisteredEventType(const QObject *object, Event::Slot slot);

	private slots:
		void registerEventType(const QObject *object, Event::Slot slot);
		void deregisterEventType(const QObject *object, Event::Slot slot);

	private:
		TypeId m_eventTypeId;

	friend class EventDispatcher;
	};

	class MTQ_EXPORT_MTQ EventDispatcher
	{
		MTQ_SINGLETON(EventDispatcher)

	public:
		typedef Event* (*CreateInstanceMethod)();

		bool emitEvent(Event::Ptr event);
		void registerForEvent(const QObject *object, const QString &eventTypeName, const TypeId &eventTypeId, const CreateInstanceMethod &method, Event::Slot slot);
		void deregisterForEvent(const QObject *object, const QString &eventTypeName, const TypeId &eventTypeId, const CreateInstanceMethod &method, Event::Slot slot);

	private:
		const TypeId getEventTypeId(const QString &eventTypeName) const;
		EventEmitter::Ptr getOrCreateEmitter(const TypeId &eventTypeId);
		void registerEventType(const QString &eventTypeName, const TypeId &eventTypeId, const CreateInstanceMethod &method);
		Event *createNewEvent(const QString &eventTypeName) const;

		QMap<TypeId::Key, EventEmitter::Ptr> m_eventEmitter;
		QMap<TypeId::Key, CreateInstanceMethod> m_instanceMethods;
		QMap<QString, TypeId> m_eventTypeIds;

		QMutex m_registerMutex;

	friend class Application;
	};

}
