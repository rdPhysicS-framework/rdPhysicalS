#ifndef	__AREA_LIGHT_H__
#define	__AREA_LIGHT_H__

#include "..\base\Light.h"

RDPS_BEGIN
	FRWK_BEGIN

		class AreaLight : public Light
		{
		private:
			int indexObject;

		public:
			AreaLight(const int index);
			AreaLight(const AreaLight &other);
			~AreaLight();

			AreaLight &SetIndexObject(const int index);
			int GetIndexObject() const;

			AreaLight &operator=(const AreaLight &other);
			virtual Light *Clone() const;
		};

	FRWK_END
RDPS_END

#endif//__AREA_LIGHT_H__