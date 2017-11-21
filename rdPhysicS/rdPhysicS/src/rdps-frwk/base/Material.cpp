#include "Material.h"
#include "..\material\brdf\BRDF.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_FRWK

Material::Material(const TypeMaterial _type) :
		  ambient(new BRDF()),
		  type(_type),
		  shadow(true)
{}

Material::Material(const RT::Vec3f &color, 
				   const float _ambient,
				   const TypeMaterial _type) :
		  ambient(new BRDF(color, _ambient, AMBIENT)),
		  type(_type),
		  shadow(true)
{}

Material::Material(BRDF *_ambient,
				   const TypeMaterial _type) :
		  ambient(_ambient),
		  type(_type),
		  shadow(true)
{}

Material::Material(const Material &other) :
		  ambient(other.ambient->Clone()),
		  type(other.type),
		  shadow(other.shadow)
{}

Material::~Material()
{
	if (ambient)
		delete ambient;
}

Material &Material::operator=(const Material &other)
{
	*ambient = *other.ambient;
	return (*this);
}

BRDF *Material::GetAmbient() const
{
	return ambient;
}

bool Material::GetShadow() const
{
	return shadow;
}

TypeMaterial Material::GetType() const
{
	return type;
}

Material &Material::SetAmbient(BRDF *_ambient)
{
	if (!ambient)
		ambient = _ambient;

	*ambient = *_ambient;

	return (*this);
}

Material &Material::SetAmbientK(const float _ambient)
{
	if (!ambient)
		Logger::Log("Attribute ambient of the material class is null.");
	
	ambient->SetK(_ambient);
	return (*this);
}

Material &Material::SetShadow(const bool _shadow)
{
	shadow = _shadow;
	return (*this);
}

