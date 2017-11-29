#ifndef	__RECTANGLE_H__
#define	__RECTANGLE_H__

#include "..\base\EmissiveObject.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class Rectangle : public EmissiveObject
		{
		private:
			RT::Vec3f p;
			RT::Vec3f a;
			RT::Vec3f b;
			RT::Vec3f normal;

		public:
			Rectangle(const RT::Vec3f &_p,
					  const RT::Vec3f &_a,
					  const RT::Vec3f &_b,
					  Material *material);
			Rectangle(const RT::Vec3f &_p,
					  const RT::Vec3f &_a,
					  const RT::Vec3f &_b,
					  const RT::Vec3f &_normal,
					   Material *material);
			Rectangle(const Rectangle &other);
			~Rectangle();

			RT::Vec3f GetP() const;
			RT::Vec3f GetA() const;
			RT::Vec3f GetB() const;
			RT::Vec3f GetNormal() const;

			virtual Rectangle *Clone() const;
			Rectangle &operator=(const Rectangle &other);
		};

	FRWK_END
RDPS_END

#endif//__RECTANGLE_H__
