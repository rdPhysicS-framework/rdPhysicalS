#ifndef	__SPHERICAL_LAMP_H__
#define	__SPHERICAL_LAMP_H__

#include "..\base\EmissiveObject.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class SphericalLamp : public EmissiveObject
		{
		private:
			RT::Vec3f center;
			float radius;

		public:
			SphericalLamp(const float _radius);
			SphericalLamp(const RT::Vec3f &_center = BLACK,
						  const float _radius = 0.0f,
						  Material *material = nullptr);
			SphericalLamp(const SphericalLamp &other);
			~SphericalLamp();

			const RT::Vec3f &GetCenter() const;
			float GetRadius() const;
			SphericalLamp &SetRadius(const float _radius);
			SphericalLamp &SetCenter(const RT::Vec3f &_center);

			virtual SphericalLamp *Clone() const;
			SphericalLamp &operator=(const SphericalLamp &other);

		};

	FRWK_END
RDPS_END

#endif//__SPHERICAL_LAMP_H__