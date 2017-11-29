#include "EmissiveMaterial.h"

USING_RDPS
USING_FRWK

EmissiveMaterial::EmissiveMaterial(const RT::Vec3f &_color, 
								   const float _ls) :
				  Material(EMISSIVE_MATERIAL),
				  color(_color),
				  ls(_ls)
{}

EmissiveMaterial::EmissiveMaterial(const EmissiveMaterial &other) :
				  Material(other),
				  color(other.color),
				  ls(other.ls)
{}

EmissiveMaterial::~EmissiveMaterial()
{}

const RT::Vec3f &EmissiveMaterial::GetColor() const
{
	return color;
}

float EmissiveMaterial::GetLs() const
{
	return ls;
}

EmissiveMaterial *EmissiveMaterial::Clone() const
{
	return new EmissiveMaterial(*this);
}

EmissiveMaterial &EmissiveMaterial::operator=(const EmissiveMaterial & other)
{
	Material::operator=(other);
	color = other.color;
	ls = other.ls;
	return (*this);
}

EmissiveMaterial &EmissiveMaterial::SetColor(const RT::Vec3f &_color)
{
	color = _color;
	return (*this);
}

EmissiveMaterial &EmissiveMaterial::SetColor(const float r, const float g, const float b)
{
	color.Set(r, g, b);
	return (*this);
}
