#include "AmbientOccluder.h"

USING_RDPS
USING_FRWK

AmbientOccluder::AmbientOccluder(const RT::Vec3f &_color, 
								 const float _ls, 
								 const float _minAmount) :
				 Light(false, AMBIENT_OCCLUDER_LIGHT),
				 color(_color),
				 ls(_ls),
				 minAmount(_minAmount)
{}

AmbientOccluder::AmbientOccluder(const AmbientOccluder &other) :
	Light(other),
	color(other.color),
	ls(other.ls),
	minAmount(other.minAmount)
{}

AmbientOccluder::~AmbientOccluder()
{}

AmbientOccluder *AmbientOccluder::Clone() const
{
	return new AmbientOccluder(*this);
}

AmbientOccluder &AmbientOccluder::operator=(const AmbientOccluder &other)
{
	Light::operator=(other);
	color = other.color;
	ls = other.ls;
	minAmount = other.minAmount;

	return (*this);
}

const RT::Vec3f &AmbientOccluder::GetColor() const
{
	return color;
}

float AmbientOccluder::GetLs() const
{
	return ls;
}

float AmbientOccluder::GetMinAmount() const
{
	return minAmount;
}

AmbientOccluder &AmbientOccluder::SetColor(const RT::Vec3f &_color)
{
	color = _color;
	return (*this);
}

AmbientOccluder &AmbientOccluder::SetColor(const float r, const float g, const float b)
{
	color.Set(r, g, b);
	return (*this);
}

AmbientOccluder &AmbientOccluder::Setls(const float _ls)
{
	ls = _ls;
	return (*this);
}

AmbientOccluder &AmbientOccluder::SetMinAmount(const float _minAmount)
{
	minAmount = _minAmount;
	return (*this);
}
