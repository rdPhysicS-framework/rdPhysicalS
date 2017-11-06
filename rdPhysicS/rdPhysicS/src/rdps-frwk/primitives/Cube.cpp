#include "Cube.h"
#include "..\base\Material.h"

USING_RDPS
USING_FRWK

Cube::Cube(const RT::Vec3f &_initPoint,
		   const RT::Vec3f &_size, 
		   Material *material) :
	  GeometricObject(material, 
					  CUBE),
	  initPoint(_initPoint),
	  size(_size)
{}

Cube::Cube(const RT::Vec3f &_size) :
	  GeometricObject(nullptr, CUBE),
	  initPoint(BLACK),
	  size(_size)
{}

Cube::Cube(const Cube &other) :
	  GeometricObject(other),
	  initPoint(other.initPoint),
	  size(other.size)
{}

Cube::~Cube()
{}

Cube *Cube::Clone() const
{
	return new Cube(*this);
}

Cube &Cube::operator=(const Cube &other)
{
	GeometricObject::operator=(other);
	return (*this);
}

Cube &Cube::SetInitPoint(const RT::Vec3f &_initPoint)
{
	initPoint = _initPoint;
	return (*this);
}

Cube &Cube::SetSize(const RT::Vec3f &_size)
{
	size = _size;
	return (*this);
}
