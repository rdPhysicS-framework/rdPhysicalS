#include "BRDF.h"
#include "..\..\..\Util\LogError.h"

USING_RDPS
USING_FRWK

BRDF::BRDF(const RT::Vec3f &_color, 
		   const float _k,
		   const TypeBRDF _type) :
	  color(_color),
	  k(_k),
	  type(_type)
{}

BRDF::BRDF(const BRDF &other) :
	  color(other.color),
	  k(other.k),
	  type(other.type)
{}

BRDF::BRDF(const TypeBRDF _type) :
	  color(),
	  k(0.0f),
	  type(_type)
{}

BRDF::~BRDF()
{}

BRDF *BRDF::Clone() const
{
	return new BRDF(*this);
}

BRDF &BRDF::operator=(const BRDF &other)
{
	if (other.type != type)
		Logger::Log("ERROR  when doing the copies of the data."
					" Component type different BRDF.");

	color = other.color;
	k = other.k;
	return (*this);
}

const RT::Vec3f &BRDF::GetColor() const
{
	return color;
}

float BRDF::GetK() const
{
	return k;
}

TypeBRDF BRDF::GetType() const
{
	return type;
}

BRDF &BRDF::SetColor(const RT::Vec3f &_color)
{
	color = _color;
	return (*this);
}

BRDF &BRDF::SetK(const float _k)
{
	k = _k;
}
