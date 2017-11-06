#include "ObjectBase.h"

USING_RDPS
USING_FRWK

ObjectBase::ObjectBase(const TypeObject &_type) :
			type(_type)
{}

ObjectBase::ObjectBase(const ObjectBase &other) :
			type(other.type)
{}

ObjectBase &ObjectBase::operator=(const ObjectBase & other)
{
	type = other.type;
	return (*this);
}
