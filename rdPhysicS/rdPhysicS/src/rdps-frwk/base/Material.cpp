#include "Material.h"

USING_RDPS
USING_FRWK

Material::Material(const TypeMaterial _type) :
	      type(_type)
{}

Material::Material(const Material &other) :
		  type(other.type)
{}

Material::~Material()
{}

Material &Material::operator=(const Material & other)
{
	type = other.type;
	return (*this);
}

TypeMaterial Material::GetType() const
{
	return type;
}
