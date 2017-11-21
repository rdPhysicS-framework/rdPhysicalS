#include "GlossySpecular.h"

USING_RDPS
USING_FRWK

GlossySpecular::GlossySpecular(const RT::Vec3f &_color, 
							   const float _k, 
							   const float _exp) :
			    BRDF(_color, _k, GLOSSY_SPECULAR),
			    exp(_exp)
{}

GlossySpecular::GlossySpecular(const GlossySpecular &other) :
				BRDF(other),
				exp(other.exp)

{}

GlossySpecular::~GlossySpecular()
{}

GlossySpecular *GlossySpecular::Clone() const
{
	return new GlossySpecular(*this);
}

GlossySpecular &GlossySpecular::operator=(const GlossySpecular &other)
{
	BRDF::operator=(other);
	exp = other.exp;
	return (*this);
}

float GlossySpecular::GetExp() const
{
	return exp;
}

GlossySpecular &GlossySpecular::SetExp(const float _exp)
{
	exp = _exp;
	return (*this);
}
