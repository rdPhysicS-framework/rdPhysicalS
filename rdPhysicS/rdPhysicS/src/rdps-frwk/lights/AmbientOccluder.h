#ifndef	__AMBIENT_OCCLUDER_H__
#define	__AMBIENT_OCCLUDER_H__

#include "..\base\Light.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class AmbientOccluder : public Light
		{
		private:
			RT::Vec3f color;
			float ls;
			float minAmount;

		public:
			AmbientOccluder(const RT::Vec3f &_color,
							const float _ls,
							const float _minAmount);
			AmbientOccluder(const AmbientOccluder &other);
			~AmbientOccluder();

			virtual AmbientOccluder *Clone() const;

			AmbientOccluder &operator=(const AmbientOccluder &other);

			const RT::Vec3f &GetColor() const;
			float GetLs() const;
			float GetMinAmount() const;

			AmbientOccluder &SetColor(const RT::Vec3f &_color);
			AmbientOccluder &SetColor(const float r, const float g, const float b);
			AmbientOccluder &Setls(const float _ls);
			AmbientOccluder &SetMinAmount(const float _minAmount);
		};

	FRWK_END
RDPS_END

#endif//__AMBIENT_OCCLUDER_H__