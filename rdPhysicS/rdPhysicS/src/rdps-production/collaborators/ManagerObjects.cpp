#include "ManagerObjects.h"
#include "..\..\rdps-frwk\base\GeometricObject.h"

USING_RDPS
USING_PDCT

ManagerObjects::ManagerObjects() :
	Collaborator(MANAGER_OF_OBJECTS),
	package(new ObjectsHostPkg())
{}

ManagerObjects::ManagerObjects(const ManagerObjects &other) :
	Collaborator(other),
	package(other.package)
{}

ManagerObjects::~ManagerObjects()
{}

const int ManagerObjects::AddObject(FRWK GeometricObject * object)
{
	return package->AddObject(object);
}

ManagerObjects &ManagerObjects::RemoveObject(const int id)
{
	package->RemoveObject(id);
	return (*this);
}

const int ManagerObjects::AddLight(FRWK Light *light)
{
	return package->AddLight(light);
}

ManagerObjects &ManagerObjects::RemoveLight(const int id)
{
	package->RemoveLight(id);
	return (*this);
}

ManagerObjects &ManagerObjects::SetViewPlane(FRWK ViewPlane * vp)
{
	package->SetViewPlane(vp);
	return (*this);
}

ManagerObjects &ManagerObjects::SetCamera(FRWK Camera *camera)
{
	package->SetCamera(camera);
	return (*this);
}

ManagerObjects *ManagerObjects::Clone()
{
	return new ManagerObjects(*this);
}

ManagerObjects &ManagerObjects::Init()
{
	return (*this);
}

ManagerObjects &ManagerObjects::ExecuteFunction()
{
	return (*this);
}

ManagerObjects &ManagerObjects::Exit()
{
	return (*this);
}

bool ManagerObjects::HandleMessage(const Message & message)
{
	return false;
}
