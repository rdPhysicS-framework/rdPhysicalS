#include "Light.h"

USING_RDPS
USING_FRWK

Light::Light(const TypeLight _type) :
	   shadow(true),
	   type(_type)
{}

Light::Light(bool _shadow, 
			 TypeLight _type) :
	   shadow(_shadow),
	   type(_type)
{}

Light::Light(const Light &other) :
	   shadow(other.shadow),
	   type(other.type)
{}

Light &Light::operator=(const Light & other)
{
	shadow = other.shadow;
	type = other.type;
	return (*this);
}

bool Light::GetShadow() const
{
	return shadow;
}

TypeLight Light::GetType() const
{
	return type;
}

Light &Light::SetShadow(const bool _shadow)
{
	shadow = _shadow;
	return (*this);
}
