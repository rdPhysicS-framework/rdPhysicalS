#include "PhongMaterial.h"
#include "brdf\GlossySpecular.h"

USING_RDPS
USING_FRWK

PhongMaterial::PhongMaterial() :
			   Material(PHONG_MATERIAL)
{}

PhongMaterial::PhongMaterial(BRDF *_ambient,
							 BRDF *_diffuse, 
							 GlossySpecular *_specular) :
			   Material(_ambient, PHONG_MATERIAL),
			   diffuse(_diffuse),
			   specular(_specular)
{}

PhongMaterial::PhongMaterial(const RT::Vec3f &color,
							 const float _ambient, 
							 const float _diffuse, 
							 const float _specular, 
							 const float _intensity) :
				Material(new BRDF(color, _ambient, AMBIENT), PHONG_MATERIAL),
				diffuse(new BRDF(color, _diffuse, DIFFUSE)),
				specular(new GlossySpecular(color, _specular, _intensity))
{}

PhongMaterial::PhongMaterial(const PhongMaterial &other) :
			   Material(other),
			   diffuse(other.diffuse->Clone()),
			   specular(other.specular->Clone())
{}

PhongMaterial::~PhongMaterial()
{
	if (diffuse)
		delete diffuse;
	if (specular)
		delete specular;
}

PhongMaterial *PhongMaterial::Clone() const
{
	return new PhongMaterial(*this);
}

PhongMaterial &PhongMaterial::operator=(const PhongMaterial &other)
{
	*ambient = *other.ambient;
	*diffuse = *other.diffuse;
	*specular = *other.specular;
	return (*this);
}

BRDF *PhongMaterial::GetDiffuse() const
{
	return diffuse;
}

GlossySpecular *PhongMaterial::GetSpecular() const
{
	return specular;
}

PhongMaterial &PhongMaterial::SetDiffuse(BRDF * _diffuse)
{
	*diffuse = *_diffuse;
	return (*this);
}

PhongMaterial &PhongMaterial::SetSpecular(GlossySpecular *_specular)
{
	if (!specular)
		specular = _specular;

	*specular = *_specular;
	return (*this);
}

PhongMaterial &PhongMaterial::SetColor(const RT::Vec3f &color)
{
	ambient->SetColor(color);
	diffuse->SetColor(color);
	specular->SetColor(color);
	return (*this);
}

PhongMaterial &PhongMaterial::SetColor(const float r, const float g, const float b)
{
	ambient->SetColor(RT::Vec3f(r, g, b));
	diffuse->SetColor(RT::Vec3f(r, g, b));
	specular->SetColor(RT::Vec3f(r, g, b));
	return (*this);
}

PhongMaterial &PhongMaterial::SetDiffuseK(const float _diffuse)
{
	diffuse->SetK(_diffuse);
	return (*this);
}

PhongMaterial &PhongMaterial::SetSpecularK(const float _specular)
{
	specular->SetK(_specular);
	return (*this);
}

PhongMaterial &PhongMaterial::SetIntensity(const float intensity)
{
	specular->SetExp(intensity);
	return (*this);
}
