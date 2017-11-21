#include "AmbientLight.h"

USING_RDPS
USING_FRWK

AmbientLight::AmbientLight(const RT::Vec3f &_color, 
						   const float _ls) :
			  Light(false, AMBIENT_LIGHT),
			  color(_color),
			  ls(_ls)
{}

AmbientLight::AmbientLight(const AmbientLight &other) :
			  Light(other),
			  color(other.color),
			  ls(other.ls)
{}

AmbientLight::~AmbientLight()
{}

AmbientLight *AmbientLight::Clone() const
{
	return new AmbientLight(*this);
}

AmbientLight &AmbientLight::operator=(const AmbientLight &other)
{
	Light::operator=(other);
	color = other.color;
	ls = other.ls;
	return (*this);
}

const RT::Vec3f & AmbientLight::GetColor() const
{
	return color;
}

float AmbientLight::GetLs() const
{
	return ls;
}

AmbientLight &AmbientLight::SetColor(const RT::Vec3f &_color)
{
	color = _color;
	return (*this);
}

AmbientLight &AmbientLight::SetColor(const float r, 
									 const float g, 
									 const float b)
{
	color = RT::Vec3f(r, g, b);
	return (*this);
}

AmbientLight &AmbientLight::Setls(const float _ls)
{
	ls = _ls;
	return (*this);
}
