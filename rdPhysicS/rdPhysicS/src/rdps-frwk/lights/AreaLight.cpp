#include "AreaLight.h"

USING_RDPS
USING_FRWK

AreaLight::AreaLight(const int index) :
		   Light(AREA_LIGHT),
		   indexObject(index)
{}

AreaLight::AreaLight(const AreaLight &other) :
		   Light(other),
		   indexObject(other.indexObject)
{}

AreaLight::~AreaLight()
{}

AreaLight &AreaLight::SetIndexObject(const int index)
{
	indexObject = index;
	return (*this);
}

int AreaLight::GetIndexObject() const
{
	return indexObject;
}

AreaLight &AreaLight::operator=(const AreaLight & other)
{
	Light::operator=(other);
	indexObject = other.indexObject;

	return (*this);
}

Light *AreaLight::Clone() const
{
	return new AreaLight(*this);
}
