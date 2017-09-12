#ifndef	 __RT_TRANSFORM_H__
#define	 __RT_TRANSFORM_H__

#include <RTmath.h>
#include "assets\Config.h"

namespace RT
{
	class Transform
	{
	private:
		RT::Mat4f invMatrix;
		//static Transform *instance;

	public:
		Transform();
		~Transform();

		//static Transform *Get();
		Transform &Translate(const float x, const float y, const float z);
		Transform &Translate(const RT::Vec3f &pos);
		Transform &RotateX(const float angle);
		Transform &RotateY(const float angle);
		Transform &RotateZ(const float angle);
		Transform &Scale(const float x, const float y, const float z);
		Transform &Scale(const RT::Vec3f &scale);
		Transform &Scale(const float scale);
		void ThisObject(RT_Primitive &object);
	};
}

#endif //__RT_TRANSFORM_H__
