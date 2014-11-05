#include "TypeId.h"

using namespace mtq;

TypeId::TypeId(const QMetaObject *metaObject)
	: m_metaObject(metaObject)
{
}

TypeId::Key TypeId::key() const
{
	return (Key)m_metaObject;
}

TypeId TypeId::parent() const
{
	return TypeId(m_metaObject->superClass());
}

bool TypeId::operator ==(const TypeId &other) const
{
	return key() == other.key();
}

bool TypeId::operator !=(const TypeId &other) const
{
	return key() != other.key();
}
