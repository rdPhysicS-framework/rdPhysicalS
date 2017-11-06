#ifndef	__PLANE_H__
#define	__PLANE_H__

#include "..\base\GeometricObject.h"

RDPS_BEGIN
	FRWK_BEGIN

		class Plane : public GeometricObject
		{
		private:
			RT::Vec3f point;
			RT::Vec3f normal;

		public:
			Plane(const RT::Vec3f &_pont, 
				  const RT::Vec3f &_normal,
				  Material *material = nullptr);
			Plane(const Plane &other);
			~Plane();

			virtual Plane *Clone() const;
			Plane &operator=(const Plane &other);

			inline const RT::Vec3f &GetPoint() const { return point; }
			inline const RT::Vec3f &GetNormal() const { return normal; }
		};

	FRWK_END
RDPS_END

#endif//__PLANE_H__