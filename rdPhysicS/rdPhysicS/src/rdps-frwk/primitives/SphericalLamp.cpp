#include "SphericalLamp.h"

USING_RDPS
USING_FRWK

SphericalLamp::SphericalLamp(const float _radius) :
	EmissiveObject(SPHERICAL, nullptr),
	radius(_radius),
	center()
{}

SphericalLamp::SphericalLamp(const RT::Vec3f &_center,
						     const float _radius,
						     Material *material) :
	EmissiveObject(SPHERICAL, material),
	center(_center),
	radius(_radius)
{}

SphericalLamp::SphericalLamp(const SphericalLamp &other) :
	EmissiveObject(other),
	center(other.center),
	radius(other.radius)
{}

SphericalLamp::~SphericalLamp()
{}

SphericalLamp *SphericalLamp::Clone() const
{
	return new SphericalLamp(*this);
}

SphericalLamp &SphericalLamp::operator=(const SphericalLamp &other)
{
	EmissiveObject::operator=(other);
	center = other.center;
	radius = other.radius;
	return (*this);
}

float SphericalLamp::GetRadius() const
{
	return radius;
}

const RT::Vec3f &SphericalLamp::GetCenter() const
{
	return center;
}

SphericalLamp &SphericalLamp::SetRadius(const float _radius)
{
	radius = _radius;
	return (*this);
}

SphericalLamp &SphericalLamp::SetCenter(const RT::Vec3f &_center)
{
	center = _center;
	return (*this);
}
