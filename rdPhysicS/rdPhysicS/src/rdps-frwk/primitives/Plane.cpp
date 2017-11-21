#include "Plane.h"

USING_RDPS
USING_FRWK

Plane::Plane(const RT::Vec3f &_point, 
			 const RT::Vec3f &_normal, 
			 Material *material) :
	   GeometricObject(material, 
					   PLANE),
	   point(_point),
	   normal(_normal)
{}

Plane::Plane(const Plane &other) :
	   GeometricObject(other),
	   point(other.point),
	   normal(other.normal)
{}

Plane::~Plane()
{}

Plane *Plane::Clone() const
{
	return new Plane(*this);
}

Plane &Plane::operator=(const Plane &other)
{
	GeometricObject::operator=(other);
	point = other.point;
	normal = other.normal;
	return (*this);
}

const RT::Vec3f &Plane::GetPoint() const
{
	return point;
}

const RT::Vec3f &Plane::GetNormal() const
{
	return normal;
}
