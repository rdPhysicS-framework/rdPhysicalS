#ifndef	__AMBIENT_LIGHT_H__
#define	__AMBIENT_LIGHT_H__

#include "..\base\Light.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class AmbientLight : public Light
		{
		private:
			RT::Vec3f color;
			float ls;

		public:
			AmbientLight(const RT::Vec3f &_color = WHITE, 
						 const float _ls = 1.0f);
			AmbientLight(const AmbientLight &other);
			~AmbientLight();

			virtual AmbientLight *Clone() const;

			AmbientLight &operator=(const AmbientLight &other);

			inline const RT::Vec3f &GetColor() const { return color; }
			inline float GetLs() const { return ls; }

			AmbientLight &SetColor(const RT::Vec3f &_color);
			AmbientLight &SetColor(const float r, const float g, const float b);
			AmbientLight &Setls(const float _ls);
		};

	FRWK_END
RDPS_END

#endif//__AMBIENT_LIGHT_H__