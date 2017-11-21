#include "GeometricObject.h"
#include "Material.h"

USING_RDPS
USING_FRWK

GeometricObject::GeometricObject(Material *_material, 
								 const TypeObject type) :
				 ObjectBase(type),
				 material(_material)
{}

//GeometricObject::GeometricObject(Material *_material,
//								 const TypeObject type,
//								 const RT::Vec3f &position, 
//								 const RT::Vec3f &rotation, 
//								 const RT::Vec3f &scale) :
//	ObjectBase(type),
//	Actor(),
//	material(_material)
//{}

GeometricObject::GeometricObject(const GeometricObject &other) :
				 ObjectBase(other),
				 Actor(other),
				 material(other.material->Clone())
{}

GeometricObject::~GeometricObject()
{
	if (material)
		delete material;
}

GeometricObject &GeometricObject::operator=(const GeometricObject &other)
{
	ObjectBase::operator=(other);
	Actor::operator=(other);
	*material = *other.material;
	return (*this);
}

Material *GeometricObject::GetMaterial() const
{
	return material;
}

GeometricObject &GeometricObject::SetMaterial(const Material &_material)
{
	*material = _material;
	return (*this);
}
