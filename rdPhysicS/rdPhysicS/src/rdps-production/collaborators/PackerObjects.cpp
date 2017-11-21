#include "PackerObjects.h"
#include "..\states\StateMachine.h"
#include "..\states\state-global\ToRest.h"
#include "..\..\rdps-packages\input\Container.h"
#include "..\Util\ObjectsHostPkg.h"

USING_RDPS
USING_PDCT
USING_PKG

PackerObjects::PackerObjects(Container *_container) :
	Collaborator(PACKER_OF_OBJECTS, 
				 new StateMachine(this)),
	container(_container),
	package(nullptr)
{
	stateMachine->SetCurrentState(ToRest::Get());
}

PackerObjects::PackerObjects(const PackerObjects &other) :
	Collaborator(other),
	container(other.container),
	package(other.package)
{}

PackerObjects::~PackerObjects()
{}

const ObjectsHostPkg *PackerObjects::GetPackage() const
{
	return package;
}

PKG Container *PackerObjects::GetContainer() const
{
	return container;
}

PackerObjects &PackerObjects::SetPackage(const ObjectsHostPkg *_package)
{
	package = _package;
	return (*this);
}

PackerObjects &PackerObjects::SetContainer(PKG Container *_container)
{
	container = _container;
	return (*this);
}

PackerObjects *PackerObjects::Clone()
{
	return new PackerObjects(*this);
}

PackerObjects &PackerObjects::Init()
{
	stateMachine->GetCurrentState()->Enter(*this);
	return (*this);
}

PackerObjects &PackerObjects::ExecuteFunction()
{
	stateMachine->Update();
	return (*this);
}

PackerObjects &PackerObjects::Exit()
{
	stateMachine->GetCurrentState()->Exit(*this);
	return (*this);
}

