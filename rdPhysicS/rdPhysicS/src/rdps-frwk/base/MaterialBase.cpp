#include "MaterialBase.h"
#include "..\material\brdf\BRDF.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_FRWK

MaterialBase::MaterialBase(const TypeMaterial _type) :
		  Material(_type),
		  ambient(new BRDF()),
		  shadow(true)
{}

MaterialBase::MaterialBase(const RT::Vec3f &color, 
				   const float _ambient,
				   const TypeMaterial _type) :
		  Material(_type),
		  ambient(new BRDF(color, _ambient, AMBIENT)),
		  shadow(true)
{}

MaterialBase::MaterialBase(BRDF *_ambient,
				   const TypeMaterial _type) :
		  Material(_type),
		  ambient(_ambient),
		  shadow(true)
{}

MaterialBase::MaterialBase(const MaterialBase &other) :
		  Material(other),
		  ambient(other.ambient->Clone()),
		  shadow(other.shadow)
{}

MaterialBase::~MaterialBase()
{
	if (ambient)
		delete ambient;
}

MaterialBase &MaterialBase::operator=(const MaterialBase &other)
{
	*ambient = *other.ambient;
	return (*this);
}

BRDF *MaterialBase::GetAmbient() const
{
	return ambient;
}

bool MaterialBase::GetShadow() const
{
	return shadow;
}

MaterialBase &MaterialBase::SetAmbient(BRDF *_ambient)
{
	if (!ambient)
		ambient = _ambient;

	*ambient = *_ambient;

	return (*this);
}

MaterialBase &MaterialBase::SetAmbientK(const float _ambient)
{
	if (!ambient)
		Logger::Log("Attribute ambient of the material class is null.");
	
	ambient->SetK(_ambient);
	return (*this);
}

MaterialBase &MaterialBase::SetShadow(const bool _shadow)
{
	shadow = _shadow;
	return (*this);
}

