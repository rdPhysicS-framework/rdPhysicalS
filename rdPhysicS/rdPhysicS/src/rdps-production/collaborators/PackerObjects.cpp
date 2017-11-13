#include "PackerObjects.h"

USING_RDPS
USING_PDCT

PackerObjects::PackerObjects(Container *_container) :
	Collaborator(PACKER_OF_OBJECTS),
	container(_container),
	package(nullptr)
{}

PackerObjects::PackerObjects(const PackerObjects &other) :
	Collaborator(other),
	container(other.container),
	package(other.package)
{}

PackerObjects::~PackerObjects()
{}

PackerObjects *PackerObjects::Clone()
{
	return new PackerObjects(*this);
}

PackerObjects &PackerObjects::Init()
{
	return (*this);
}

PackerObjects &PackerObjects::ExecuteFunction()
{
	return (*this);
}

PackerObjects &PackerObjects::Exit()
{
	return (*this);
}

bool PackerObjects::HandleMessage(const Message &message)
{
	return false;
}

