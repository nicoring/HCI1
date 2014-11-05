#pragma once

#include <QMetaObject>

namespace mtq {

	class MTQ_EXPORT_MTQ TypeId
	{
	public:
		typedef uint Key;

		TypeId(const QMetaObject *metaObject);

		Key key() const;
		TypeId parent() const;

		bool operator == (const TypeId &other) const;
		bool operator != (const TypeId &other) const;

	private:
		const QMetaObject *m_metaObject;
	};

}
