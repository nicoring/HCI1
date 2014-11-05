#pragma once

#include <QSharedPointer>

#include "mtq/utils/TypeId.h"

#ifndef STRINGIFY
	#define QUOTE(str) #str
	#define STRINGIFY(str) QUOTE(str)
#endif

#define MTQ_EVENT(EventT) \
	public: \
		typedef QSharedPointer<const EventT> Ptr; \
		EventT() {}; \
		static Event* createInstance() { return new EventT(); } \
		static QString staticTypeName() { return STRINGIFY(EventT); } \
		static TypeId staticTypeId() { return TypeId(&staticMetaObject); } \
		virtual QString typeName() const { return STRINGIFY(EventT); } \
		virtual TypeId typeId() const { return TypeId(metaObject()); } \
		static QSharedPointer<const EventT> fromEvent(Event::Ptr event) { return event.dynamicCast<const EventT>(); }

#define MTQ_EVENT_PROPERTY(Type, Name) \
	public: \
		void Name(const Type &value) { m_##Name = value; } \
		Type Name() const { return m_##Name; } \
	private: \
		Type m_##Name;

#define MTQ_EVENT_POINTER_PROPERTY(Type, Name) \
	public: \
		void Name(const Type value) { m_##Name = value; } \
		const Type Name() const { return m_##Name; } \
	private: \
		const Type m_##Name;

namespace mtq {

	class MTQ_EXPORT_MTQ Event : public QObject
	{
		Q_OBJECT
	public:
		typedef const char* Slot;

		MTQ_EVENT(Event)
	};

	Q_DECLARE_METATYPE(Event::Ptr)
}
