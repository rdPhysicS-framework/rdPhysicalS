#ifndef	__REFLECTIVE_MATERIAL_H__
#define	__REFLECTIVE_MATERIAL_H__

#include "..\base\MaterialBase.h"

RDPS_BEGIN
	FRWK_BEGIN
		
		class GlossySpecular;

		class ReflectiveMaterial : public MaterialBase
		{
		private:
			BRDF *diffuse;
			GlossySpecular *specular;
			BRDF *reflect;

		public:
			ReflectiveMaterial();
			ReflectiveMaterial(BRDF *_ambient,
							   BRDF *_diffuse,
							   GlossySpecular *_specular,
							   BRDF *_reflect);
			ReflectiveMaterial(const RT::Vec3f &color,
							   const float ambient,
							   const float diffuse,
							   const float specular,
							   const float intensity,
							   const float reflect);
			ReflectiveMaterial(const ReflectiveMaterial &other);
			~ReflectiveMaterial();

			ReflectiveMaterial &operator=(const ReflectiveMaterial &other);

			BRDF *GetDiffuse() const;
			GlossySpecular *GetSpecular() const;
			BRDF *GetReflect() const;

			virtual ReflectiveMaterial *Clone() const;
			virtual ReflectiveMaterial &SetColor(const RT::Vec3f &color);
			virtual ReflectiveMaterial &SetColor(const float r, const float g, const float b);

			ReflectiveMaterial &SetDiffuse(BRDF *_diffuse);
			ReflectiveMaterial &SetSpecular(GlossySpecular *_specular);
			ReflectiveMaterial &SetReflect(BRDF *_reflect);

			ReflectiveMaterial &SetDiffuseK(const float _diffuse);
			ReflectiveMaterial &SetSpecularK(const float _specular);
			ReflectiveMaterial &SetIntensity(const float _intensity);
			ReflectiveMaterial &SetReflectK(const float _reflect);
		};

	RDPS_END
FRWK_END

#endif//__REFLECTIVE_MATERIAL_H__