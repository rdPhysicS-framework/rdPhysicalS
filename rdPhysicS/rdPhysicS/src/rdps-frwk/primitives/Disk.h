#ifndef	__DISK_H__
#define	__DISK_H__

#include "..\base\EmissiveObject.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class Disk : public EmissiveObject
		{
		private:
			RT::Vec3f center;
			RT::Vec3f normal;
			float radius;

		public:
			Disk(const RT::Vec3f &_center,
				 const RT::Vec3f &_normal,
				 const float _radius,
				 Material *material);
			Disk(const Disk &other);
			~Disk();

			const RT::Vec3f &GetCenter() const;
			const RT::Vec3f &GetNormal() const;
			float GetRadius() const;

			virtual Disk *Clone() const;
			Disk &operator=(const Disk &other);
		};

	FRWK_END
RDPS_END

#endif//__DISK_H__