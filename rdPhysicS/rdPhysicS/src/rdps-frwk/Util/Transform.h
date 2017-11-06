#ifndef	__TRANSFORM_H__
#define	__TRANSFORM_H__

#include "..\..\GlobalDefs.h"
#include <RTmath.h>

RDPS_BEGIN
	FRWK_BEGIN

		class Transform
		{
		private:
			/*RT::Vec3f position;
			RT::Vec3f rotation;
			RT::Vec3f scale;*/

			RT::Mat4f invMatrix;
			RT::Mat4f forwardMatrix;

		public:
			Transform();
			/*Transform(const RT::Vec3f &_position = RT::Vec3f(0.f, 0.f, 0.f),
					  const RT::Vec3f &_rotation = RT::Vec3f(0.f, 0.f, 0.f),
					  const RT::Vec3f &_scale    = RT::Vec3f(1.f, 1.f, 1.f));*/
			Transform(const Transform &other);
			~Transform();

			Transform *Clone() const;

			Transform &operator=(const Transform &other);

			/*inline const RT::Vec3f &GetPosition() const      { return position;      }
			inline const RT::Vec3f &GetRotation() const      { return rotation;      }
			inline const RT::Vec3f &GetScale() const         { return scale;         }*/
			inline const RT::Mat4f &GetInvMatrix() const     { return invMatrix;     }
			inline const RT::Mat4f &GetForwardMatrix() const { return forwardMatrix; }

			Transform &Translate(const float x, const float y, const float z);
			Transform &Translate(const RT::Vec3f &_position);
			Transform &Rotation(const float x, const float y, const float z);
			Transform &Rotation(const RT::Vec3f &_position);
			Transform &RotateX(const float x);
			Transform &RotateY(const float y);
			Transform &RotateZ(const float z);
			Transform &Scale(const float x, const float y, const float z);
			Transform &Scale(const RT::Vec3f &_scale);
			Transform &Scale(const float _scale);

			//Transform &Apply();

			RT::Vec3f TransformPoint(const RT::Vec3f &p);
			static RT::Vec3f TransformPoint(RT::Mat4f &m, const RT::Vec3f &p);
		};

	FRWK_END
RDPS_END

#endif//__TRANSFORM_H__