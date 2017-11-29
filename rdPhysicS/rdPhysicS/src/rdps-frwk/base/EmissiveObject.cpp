#include "EmissiveObject.h"
#include "Material.h"

USING_RDPS
USING_FRWK

EmissiveObject::EmissiveObject(const TypeObjectEmissive _typeOE, 
							   Material * _material) :
				ObjectBase(EMISSIVE_OBJECT),
				typeOE(_typeOE),
				material(_material)
{}

EmissiveObject::EmissiveObject(const EmissiveObject &other) :
			    ObjectBase(other),
			    typeOE(other.typeOE),
			    material(other.material->Clone())
{}

EmissiveObject::~EmissiveObject()
{
	if (material)
		delete material;
}

EmissiveObject &EmissiveObject::operator=(const EmissiveObject & other)
{
	ObjectBase::operator=(other);
	typeOE = other.typeOE;
	*material = *other.material;
	return (*this);
}

Material *EmissiveObject::GetMaterial() const
{
	return material;
}

EmissiveObject &EmissiveObject::SetMaterial(const Material & _material)
{
	*material = _material;
	return (*this);
}
