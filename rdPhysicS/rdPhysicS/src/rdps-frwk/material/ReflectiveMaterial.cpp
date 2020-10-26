#include "ReflectiveMaterial.h"
#include "brdf\BRDF.h"
#include "brdf\GlossySpecular.h"

USING_RDPS
USING_FRWK

ReflectiveMaterial::ReflectiveMaterial() :
					MaterialBase(REFLECT_MATERIAL),
					diffuse(nullptr),
					specular(nullptr),
					reflect(nullptr)
{}

ReflectiveMaterial::ReflectiveMaterial(BRDF *_ambient, 
									   BRDF *_diffuse, 
									   GlossySpecular *_specular, 
									   BRDF *_reflect) :
					MaterialBase(_ambient, REFLECT_MATERIAL),
					diffuse(_diffuse),
					specular(_specular),
					reflect(_reflect)
{}

ReflectiveMaterial::ReflectiveMaterial(const RT::Vec3f &color, 
									   const float ambient, 
									   const float diffuse, 
									   const float specular, 
									   const float intensity, 
									   const float reflect) :
					MaterialBase(new BRDF(color, ambient, AMBIENT), REFLECT_MATERIAL),
					diffuse(new BRDF(color, diffuse, DIFFUSE)),
					specular(new GlossySpecular(color, specular, intensity)),
					reflect(new BRDF(color, reflect, AMBIENT))
{}

ReflectiveMaterial::ReflectiveMaterial(const ReflectiveMaterial &other) :
					MaterialBase(other),
					diffuse(other.diffuse->Clone()),
					specular(other.specular->Clone()),
					reflect(other.reflect->Clone())
{
}

ReflectiveMaterial::~ReflectiveMaterial()
{
	if (diffuse)
		delete diffuse;
	if (specular)
		delete specular;
	if (reflect)
		delete reflect;
}

ReflectiveMaterial &ReflectiveMaterial::operator=(const ReflectiveMaterial &other)
{
	MaterialBase::operator=(other);
	diffuse = other.diffuse->Clone();
	specular = other.specular->Clone();
	reflect = other.reflect->Clone();
	return (*this);
}

BRDF *ReflectiveMaterial::GetDiffuse() const
{
	return diffuse;
}

GlossySpecular *ReflectiveMaterial::GetSpecular() const
{
	return specular;
}

BRDF *ReflectiveMaterial::GetReflect() const
{
	return reflect;
}

ReflectiveMaterial *ReflectiveMaterial::Clone() const
{
	return new ReflectiveMaterial(*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetColor(const RT::Vec3f &color)
{
	ambient->SetColor(color);
	diffuse->SetColor(color);
	specular->SetColor(color);
	reflect->SetColor(color);
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetColor(const float r, const float g, const float b)
{
	ambient->SetColor(RT::Vec3f(r, g, b));
	diffuse->SetColor(RT::Vec3f(r, g, b));
	specular->SetColor(RT::Vec3f(r, g, b));
	reflect->SetColor(RT::Vec3f(r, g, b));
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetDiffuse(BRDF *_diffuse)
{
	*diffuse = *_diffuse;
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetSpecular(GlossySpecular *_specular)
{
	if (!specular)
		specular = _specular;

	*specular = *_specular;
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetReflect(BRDF *_reflect)
{
	*reflect = *_reflect;
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetDiffuseK(const float _diffuse)
{
	diffuse->SetK(_diffuse);
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetSpecularK(const float _specular)
{
	specular->SetK(_specular);
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetIntensity(const float _intensity)
{
	specular->SetExp(_intensity);
	return (*this);
}

ReflectiveMaterial &ReflectiveMaterial::SetReflectK(const float _reflect)
{
	reflect->SetK(_reflect);
	return (*this);
}

