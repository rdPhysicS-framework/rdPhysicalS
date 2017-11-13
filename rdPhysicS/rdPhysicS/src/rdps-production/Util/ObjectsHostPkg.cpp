#include "ObjectsHostPkg.h"
#include "..\..\rdps-frwk\base\GeometricObject.h"
#include "..\..\rdps-frwk\base\Light.h"
#include "..\..\rdps-frwk\Util\ViewPlane.h"
#include "..\..\rdps-frwk\camera\Camera.h"

USING_RDPS
USING_PDCT
USING_FRWK

ObjectsHostPkg::ObjectsHostPkg() :
	objects(),
	lights(),
	vp(nullptr),
	camera(nullptr)
{}

ObjectsHostPkg::~ObjectsHostPkg()
{
	for (auto i : objects)
	{
		delete i;
		i = nullptr;
	}
	objects.clear();

	for (auto i : lights)
	{
		delete i;
		i = nullptr;
	}
	lights.clear();

	if (vp)
		delete vp;

	if (camera)
		delete camera;
}

const int ObjectsHostPkg::AddObject(FRWK GeometricObject *object)
{
	objects.push_back(object);
	return static_cast<int>(objects.size() - 1);
}

ObjectsHostPkg &ObjectsHostPkg::RemoveObject(const int id)
{
	objects.erase(objects.begin() + id);
	return (*this);
}

const int ObjectsHostPkg::AddLight(FRWK Light *light)
{
	lights.push_back(light);
	return static_cast<int>(lights.size() - 1);
}

ObjectsHostPkg &ObjectsHostPkg::RemoveLight(const int id)
{
	lights.erase(lights.begin() + id);
	return (*this);
}

ObjectsHostPkg &ObjectsHostPkg::SetViewPlane(FRWK ViewPlane *_vp)
{
	vp = _vp;
	return (*this);
}

ObjectsHostPkg &ObjectsHostPkg::SetCamera(Camera *_camera)
{
	camera = _camera;
	return (*this);
}

