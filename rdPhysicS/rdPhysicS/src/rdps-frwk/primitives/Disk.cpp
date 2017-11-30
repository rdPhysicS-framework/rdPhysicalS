#include "Disk.h"

USING_RDPS
USING_FRWK

Disk::Disk(const RT::Vec3f &_center, 
		   const RT::Vec3f &_normal, 
		   const float _radius,
		   Material *material) :
	  EmissiveObject(CIRCULAR, material),
	  center(_center),
	  normal(RT::vc3::Normalize(_normal)),
	  radius(_radius)
{}

Disk::Disk(const Disk &other) :
	  EmissiveObject(other),
	  center(other.center),
	  normal(other.normal),
	  radius(other.radius)
{}

Disk::~Disk()
{}

const RT::Vec3f &Disk::GetCenter() const
{
	return center;
}

const RT::Vec3f &Disk::GetNormal() const
{
	return normal;
}

float Disk::GetRadius() const
{
	return radius;
}

Disk *Disk::Clone() const
{
	return new Disk(*this);
}

Disk &Disk::operator=(const Disk &other)
{
	EmissiveObject::operator=(other);
	center = other.center;
	normal = other.normal;
	radius = other.radius;

	return (*this);
}
