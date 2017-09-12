#include "Transform.h"

using namespace RT;

//Transform *Transform::instance = nullptr;

Transform::Transform() : invMatrix()
{
}

RT::Transform::~Transform()
{
	//if(instance)
		//delete instance;
}

//Transform *Transform::Get()
//{
//	if (!instance)
//		instance = new Transform;
//
//	return instance;
//}

Transform &Transform::Translate(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffTranslation(-x, -y, -z);
	//forwardMatrix = RT::mt4::AffTranslation(x, y, z) * forwardMatrix;

	return (*this);
}

Transform &Transform::Translate(const RT::Vec3f & pos)
{
	invMatrix *= RT::mt4::AffTranslation(pos*-1);
	//forwardMatrix = RT::mt4::AffTranslation(pos) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateX(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationX(ang).Transpose();
	//forwardMatrix = RT::mt4::AffRotationX(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateY(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationY(ang).Transpose();
	//forwardMatrix = RT::mt4::AffRotationY(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateZ(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationZ(ang).Transpose();
	//forwardMatrix = RT::mt4::AffRotationZ(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffScaling(1.0f / x, 1.0f / y, 1.0f / z);
	//forwardMatrix = RT::mt4::AffScaling(x, y, z) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const RT::Vec3f & scale)
{
	invMatrix *= RT::mt4::AffScaling(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
	//forwardMatrix = RT::mt4::AffScaling(scale) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const float scale)
{
	invMatrix *= RT::mt4::AffScaling(1 / scale, 1 / scale, 1 / scale);
	//forwardMatrix = RT::mt4::AffScaling(scale) * forwardMatrix;

	return (*this);
}

void Transform::ThisObject(RT_Primitive &object)
{
	//memcpy(object.invMatrix, (void*)invMatrix.GetMatrix(), sizeof(object.invMatrix));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			object.invMatrix[i][j] = invMatrix[i][j];
		}
	}
	invMatrix.Identity();
}
