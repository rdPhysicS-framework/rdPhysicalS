#include "SimpleMaterial.h"
#include "brdf\BRDF.h"

USING_RDPS
USING_FRWK

SimpleMaterial::SimpleMaterial() :
			    Material(SIMPLE_MATERIAL)
{}

SimpleMaterial::SimpleMaterial(BRDF *_ambient, 
							   BRDF *_diffuse) :
			    Material(_ambient, SIMPLE_MATERIAL),
				diffuse(_diffuse)
{}

SimpleMaterial::SimpleMaterial(const RT::Vec3f &color, 
							   const float ambient, 
							   const float diffuse) :
				Material(new BRDF(color, 
								  ambient, 
								  AMBIENT), 
						 SIMPLE_MATERIAL),
				diffuse(new BRDF(color, 
								 diffuse,
								 DIFFUSE))

{}

SimpleMaterial::SimpleMaterial(const SimpleMaterial &other) :
			    Material(other),
				diffuse(other.diffuse->Clone())
{}

SimpleMaterial::~SimpleMaterial()
{}

SimpleMaterial *SimpleMaterial::Clone() const
{
	return new SimpleMaterial(*this);
}

SimpleMaterial &SimpleMaterial::operator=(const SimpleMaterial &other)
{
	Material::operator=(other);
	*diffuse = *other.diffuse;
	return (*this);
}

BRDF *SimpleMaterial::GetDiffuse() const
{
	return diffuse;
}

SimpleMaterial &SimpleMaterial::SetDiffuse(BRDF *_diffuse)
{
	if (!diffuse)
		diffuse = _diffuse;
	*diffuse = *_diffuse;

	return (*this);
}

SimpleMaterial &SimpleMaterial::SetColor(const RT::Vec3f &color)
{
	ambient->SetColor(color);
	diffuse->SetColor(color);
	return (*this);
}

SimpleMaterial &SimpleMaterial::SetColor(const float r, const float g, const float b)
{
	ambient->SetColor(RT::Vec3f(r, g, b));
	diffuse->SetColor(RT::Vec3f(r, g, b));
	return (*this);
}

SimpleMaterial &SimpleMaterial::SetDiffuseK(const float _diffuse)
{
	diffuse->SetK(_diffuse);
	return (*this);
}
