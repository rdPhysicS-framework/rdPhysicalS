#include "ContainerBuilder.h"
#include "Container.h"
#include "base\PackageBase.h"

USING_RDPS
USING_PKG

ContainerBuilder::ContainerBuilder() :
				  container(new Container())
{}

ContainerBuilder::~ContainerBuilder()
{}

ContainerBuilder &ContainerBuilder::AddPackage(const std::string id, 
											   PackageBase *package)
{
	container->CreatePackage(id, package);
	return (*this);
}

Container *ContainerBuilder::Create()
{
	return container;
}
