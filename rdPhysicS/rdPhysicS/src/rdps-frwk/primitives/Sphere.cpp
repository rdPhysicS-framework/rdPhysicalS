#include "Sphere.h"

USING_RDPS
USING_FRWK

Sphere::Sphere(const float _radius) :
		GeometricObject(nullptr, SPHERE),
		radius(_radius),
		center()
{}

Sphere::Sphere(const RT::Vec3f &_center,
			   const float _radius,
			   Material *material) :
		GeometricObject(material, SPHERE),
		center(_center),
		radius(_radius)
{}

Sphere::Sphere(const Sphere &other) :
		GeometricObject(other),
		center(other.center),
		radius(other.radius)
{}

Sphere::~Sphere()
{}

Sphere *Sphere::Clone() const
{
	return new Sphere(*this);
}

Sphere &Sphere::operator=(const Sphere &other)
{
	GeometricObject::operator=(other);
	center = other.center;
	radius = other.radius;
	return (*this);
}

float Sphere::GetRadius() const
{
	return radius;
}

const RT::Vec3f &Sphere::GetCenter() const
{
	return center;
}

Sphere &Sphere::SetRadius(const float _radius)
{
	radius = _radius;
	return (*this);
}

Sphere &Sphere::SetCenter(const RT::Vec3f &_center)
{
	center = _center;
	return (*this);
}
