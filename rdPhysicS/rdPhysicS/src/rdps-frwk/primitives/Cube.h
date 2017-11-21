#ifndef	__CUBE_H__
#define	__CUBE_H__

#include "..\base\GeometricObject.h"

RDPS_BEGIN
	FRWK_BEGIN

	class Cube : public GeometricObject
	{
	private:
		RT::Vec3f initPoint;
		RT::Vec3f size;

	public:
		Cube(const RT::Vec3f &_initPoint = BLACK,
			 const RT::Vec3f &_size = BLACK,
			 Material *material = nullptr);
		Cube(const RT::Vec3f &_size);
		Cube(const Cube &other);
		~Cube();

		virtual Cube *Clone() const;
		Cube &operator=(const Cube &other);

		const RT::Vec3f GetInitPoint() const;
		const RT::Vec3f GetSize() const;
		Cube &SetInitPoint(const RT::Vec3f &_initPoint);
		Cube &SetSize(const RT::Vec3f &_size);
	};

	FRWK_END
RDPS_END

#endif//__CUBE_H__