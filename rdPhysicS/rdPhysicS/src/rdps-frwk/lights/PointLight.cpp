#include "PointLight.h"

USING_RDPS
USING_FRWK

PointLight::PointLight(const RT::Vec3f &_position, 
					   const RT::Vec3f &_color, 
					   const float _ls,
					   const int _indexObject,
					   bool shadow) :
		    Light(shadow, POINT_LIGHT),
			position(_position),
			color(_color),
			ls(_ls),
			indexObject(_indexObject)
{}

PointLight::PointLight(const PointLight &other) :
			Light(other),
			position(other.position),
			color(other.color),
			ls(other.ls),
			indexObject(other.indexObject)
{}

PointLight::~PointLight()
{}

int PointLight::GetIndexObject() const
{
	return indexObject;
}

PointLight &PointLight::SetIndexObject(const int index)
{
	indexObject = index;
	return (*this);
}

Light *PointLight::Clone() const
{
	return new PointLight(*this);
}

PointLight &PointLight::operator=(const PointLight &other)
{
	Light::operator=(other);
	position = other.position;
	color = other.color;
	ls = other.ls;
	indexObject = other.indexObject;
	return (*this);
}

const RT::Vec3f &PointLight::GetPosition() const
{
	return position;
}

const RT::Vec3f &PointLight::GetColor() const
{
	return color;
}

float PointLight::GetLs() const
{
	return ls;
}

PointLight &PointLight::SetColor(const RT::Vec3f &_color)
{
	color = _color;
	return (*this);
}

PointLight &PointLight::SetColor(const float r, const float g, const float b)
{
	color = RT::Vec3f(r, g, b);
	return (*this);
}

PointLight &PointLight::SetLs(const float _ls)
{
	ls = _ls;
	return (*this);
}
