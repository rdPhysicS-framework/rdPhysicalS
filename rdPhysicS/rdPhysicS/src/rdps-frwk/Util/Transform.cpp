#include "Transform.h"

USING_RDPS
USING_FRWK

Transform::Transform() :
		   invMatrix(),
		   forwardMatrix()
{}

/*Transform::Transform(const RT::Vec3f &_position, 
					 const RT::Vec3f &_rotation, 
					 const RT::Vec3f &_scale) :
			position(_position),
			rotation(_rotation),
			scale(_scale),
			invMatrix(),
			forwardMatrix()
{}*/


Transform::Transform(const Transform &other) :
		   /*position(other.position),
		   rotation(other.rotation),
		   scale(other.scale),*/
		   invMatrix(other.invMatrix),
		   forwardMatrix(other.forwardMatrix)
{}

Transform::~Transform()
{}

Transform *Transform::Clone() const
{
	return new Transform(*this);
}

Transform &Transform::operator=(const Transform &other)
{
	/*position = other.position;
	rotation = other.rotation;
	scale = other.scale;*/
	invMatrix = other.invMatrix;
	forwardMatrix = other.forwardMatrix;
	return (*this);
}

const RT::Mat4f &Transform::GetInvMatrix() const
{
	return invMatrix;
}

const RT::Mat4f & Transform::GetForwardMatrix() const
{
	return forwardMatrix;
}

Transform &Transform::Translate(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffTranslation(-x, -y, -z);
	forwardMatrix = RT::mt4::AffTranslation(x, y, z) * forwardMatrix;
	return (*this);
}

Transform &Transform::Translate(const RT::Vec3f &_position)
{
	invMatrix *= RT::mt4::AffTranslation(_position*-1);
	forwardMatrix = RT::mt4::AffTranslation(_position) * forwardMatrix;
	return (*this);
}

Transform &Transform::Rotation(const float x, const float y, const float z)
{
	float angx = RT::Math::ToRadians(x);
	float angy = RT::Math::ToRadians(y);
	float angz = RT::Math::ToRadians(z);

	invMatrix *= RT::mt4::AffRotation(angx, angy, angz).Transpose();
	forwardMatrix = RT::mt4::AffRotation(angx, angy, angz) * forwardMatrix;

	return (*this);
}

Transform &Transform::Rotation(const RT::Vec3f &_position)
{
	float angx = RT::Math::ToRadians(_position.x);
	float angy = RT::Math::ToRadians(_position.y);
	float angz = RT::Math::ToRadians(_position.z);

	invMatrix *= RT::mt4::AffRotation(angx, angy, angz).Transpose();
	forwardMatrix = RT::mt4::AffRotation(angx, angy, angz) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateX(const float x)
{
	float ang = RT::Math::ToRadians(x);

	invMatrix *= RT::mt4::AffRotationX(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationX(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateY(const float y)
{
	float ang = RT::Math::ToRadians(y);

	invMatrix *= RT::mt4::AffRotationY(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationY(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::RotateZ(const float z)
{
	float ang = RT::Math::ToRadians(z);

	invMatrix *= RT::mt4::AffRotationZ(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationZ(ang) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffScaling(1.0f/x, 1.0f/y, 1.0f/z);
	forwardMatrix = RT::mt4::AffScaling(1.0f/x, 1.0f/y, 1.0f/z) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const RT::Vec3f &_scale)
{
	invMatrix *= RT::mt4::AffScaling(1.0f/_scale.x, 1.0f/_scale.y, 1.0f/_scale.z);
	forwardMatrix = RT::mt4::AffScaling(1.0f/_scale.x, 1.0f/_scale.y, 1.0f/_scale.z) * forwardMatrix;

	return (*this);
}

Transform &Transform::Scale(const float _scale)
{
	invMatrix *= RT::mt4::AffScaling(1.0f/_scale, 1.0f/_scale, 1.0f/_scale);
	forwardMatrix = RT::mt4::AffScaling(1.0f/_scale, 1.0f/_scale, 1.0f/_scale) * forwardMatrix;

	return (*this);
}

/*Transform &Transform::Apply()
{
	Scale(scale);
	Rotation(rotation);
	Translate(position);
	return (*this);
}*/

RT::Vec3f Transform::TransformPoint(const RT::Vec3f &p)
{
	return RT::Vec3f(forwardMatrix[0][0] * p.x + forwardMatrix[0][1] * p.y + forwardMatrix[0][2] * p.z + forwardMatrix[0][3],
				     forwardMatrix[1][0] * p.x + forwardMatrix[1][1] * p.y + forwardMatrix[1][2] * p.z + forwardMatrix[1][3],
				     forwardMatrix[2][0] * p.x + forwardMatrix[2][1] * p.y + forwardMatrix[2][2] * p.z + forwardMatrix[2][3]);
}

RT::Vec3f Transform::TransformPoint(RT::Mat4f &m, const RT::Vec3f &p)
{
	return RT::Vec3f(m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3],
					 m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3],
					 m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3]);
}
