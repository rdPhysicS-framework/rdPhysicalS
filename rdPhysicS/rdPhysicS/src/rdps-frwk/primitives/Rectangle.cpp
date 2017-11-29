#include "Rectangle.h"

USING_RDPS
USING_FRWK

Rectangle::Rectangle(const RT::Vec3f &_p, 
					 const RT::Vec3f &_a, 
					 const RT::Vec3f &_b,
					 Material *material) :
		   EmissiveObject(RECTANGULAR, material),
		   p(_p), a(_a), b(_b),
		   normal(RT::vc3::Cross(_a, _b).Normalize())
{}

Rectangle::Rectangle(const RT::Vec3f &_p, 
					 const RT::Vec3f &_a, 
					 const RT::Vec3f &_b, 
					 const RT::Vec3f &_normal, 
					 Material *material) :
		   EmissiveObject(RECTANGULAR, material),
		   p(_p), a(_a), b(_b),
		   normal(RT::vc3::Normalize(_normal))
{}

Rectangle::Rectangle(const Rectangle &other) :
		   EmissiveObject(other),
		   p(other.p), a(other.a), b(other.b),
		   normal(other.normal)
{}

Rectangle::~Rectangle()
{}

RT::Vec3f Rectangle::GetP() const
{
	return p;
}

RT::Vec3f Rectangle::GetA() const
{
	return a;
}

RT::Vec3f Rectangle::GetB() const
{
	return b;
}

RT::Vec3f Rectangle::GetNormal() const
{
	return normal;
}

Rectangle *Rectangle::Clone() const
{
	return new Rectangle(*this);
}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
	EmissiveObject::operator=(other);
	p = other.p;
	a = other.a;
	b = other.b;
	normal = other.normal;
	return (*this);
}