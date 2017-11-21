#ifndef	__SPHERE_H__
#define	__SPHERE_H__

#include "..\base\GeometricObject.h"

RDPS_BEGIN
	FRWK_BEGIN

		class Sphere : public GeometricObject
		{
		private:
			RT::Vec3f center;
			float radius;

		public:
			Sphere(const float _radius);
			Sphere(const RT::Vec3f &_center = BLACK,
				   const float _radius = 0.0f,
				   Material *material = nullptr);
			Sphere(const Sphere &other);
			~Sphere();

			virtual Sphere *Clone() const;
			Sphere &operator=(const Sphere &other);
			
			float GetRadius() const;
			const RT::Vec3f &GetCenter() const;
			Sphere &SetRadius(const float _radius);
			Sphere &SetCenter(const RT::Vec3f &_center);
		};

	FRWK_END
RDPS_END

#endif//__SPHERE_H__