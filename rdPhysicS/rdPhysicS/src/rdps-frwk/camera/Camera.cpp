#include "Camera.h"
#include "..\base\SceneBase.h"
#include "..\..\rdps-packages\output\Renderer.h"

USING_RDPS
USING_FRWK

Camera::Camera(const RT::Vec3f &_eye, 
			   const RT::Vec3f &_lookAt, 
			   const RT::Vec3f &_up, 
			   const float vpDistance, 
			   const float _zoom) :
		eye(_eye),
		lookAt(_lookAt),
		up(_up),
		zoom(_zoom),
		viewPlaneDistance(vpDistance)
{}

Camera::Camera(const Camera &other) :
		eye(other.eye),
		lookAt(other.lookAt),
		up(other.up),
		zoom(other.zoom),
		viewPlaneDistance(other.viewPlaneDistance)
{
}

Camera::~Camera()
{}

Camera *Camera::Clone() const
{
	return new Camera(*this);
}

Camera &Camera::operator=(const Camera &other)
{
	eye = other.eye;
	lookAt = other.lookAt;
	up = other.up;
	u = other.u;
	v = other.v;
	w = other.w;
	exposureTime = other.exposureTime;
	zoom = other.zoom;
	viewPlaneDistance = other.viewPlaneDistance;

	return (*this);
}

const RT::Vec3f &Camera::GetEye() const
{
	return eye;
}

const RT::Vec3f &Camera::GetLookAt() const
{
	return lookAt;
}

const RT::Vec3f &Camera::GetEyeUp() const
{
	return up;
}

const RT::Vec3f &Camera::GetU() const
{
	return u;
}

const RT::Vec3f &Camera::GetV() const
{
	return v;
}

const RT::Vec3f &Camera::GetW() const
{
	return w;
}

float Camera::GetZoom() const
{
	return zoom;
}

float Camera::GetExposureTime() const
{
	return exposureTime;
}

float Camera::GetViewPlaneDistance() const
{
	return viewPlaneDistance;
}

Camera & Camera::SetZoom(const float _zoom)
{
	zoom = _zoom;
	return (*this);
}

Camera &Camera::SetExposireTime(float eTime)
{
	exposureTime = eTime;
	return (*this);
}

Camera &Camera::SetViewPlaneDistance(float vpDistance)
{
	viewPlaneDistance = vpDistance;
	return (*this);
}

Camera &Camera::ComputeUVW()
{
	w = (eye - lookAt).Normalize();

	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y > lookAt.y)
	{
		u = RT::Vec3f(0, 0, 1);
		v = RT::Vec3f(1, 0, 0);
		w = RT::Vec3f(0, 1, 0);
		return (*this);
	}

	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y < lookAt.y)
	{
		u = RT::Vec3f(1, 0, 0);
		v = RT::Vec3f(0, 0, 1);
		w = RT::Vec3f(0, -1, 0);
		return (*this);
	}

	u = RT::vc3::Cross(up, w).Normalize();
	v = RT::vc3::Cross(w, u).Normalize();

	return (*this);
}

Camera &Camera::Configure(const RT::Vec3f &_eye, 
						  const RT::Vec3f &_lookAt, 
						  const RT::Vec3f &_up, 
						  const float _viewPlaneDistance, 
						  const float _zoom)
{
	eye = _eye;
	lookAt = _lookAt;
	up = _up;
	viewPlaneDistance = _viewPlaneDistance;
	zoom = _zoom;
	return (*this);
}

void Camera::Render(SceneBase &scene)
{
	ComputeUVW();
	scene.GetRenderer()->Render();
}
