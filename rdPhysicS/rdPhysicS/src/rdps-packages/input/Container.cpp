#include "Container.h"
#include "base\PackageBase.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_PKG

Container::Container()
{}

Container::~Container()
{
	for (auto i = packages.begin(); i != packages.end(); ++i)
	{
		delete i->second;
	}
	packages.clear();
}

const PackageBase *Container::GetPackage(std::string id)
{
	if (packages.find(id) == packages.end())
	{
		Logger::Log("Attribute no exists : " + id);
	}

	return packages[id];
}


Container &Container::CreatePackage(std::string id, 
								    PackageBase *package)
{
	if (packages.find(id) != packages.end())
	{
		Logger::Log("Busy place - id: " + id);
	}
	
	packages[id] = package;
	
	return (*this);
}

Container &Container::RemoveElement(std::string id, const int element)
{
	packages[id]->RemoveElement(element);
	return (*this);
}

Container &Container::DestroyElements(std::string id)
{
	packages[id]->DestroyElements();
	return (*this);
}

Container &Container::DestroyElements()
{
	for (auto i = packages.begin(); i != packages.end(); ++i)
	{
		i->second->DestroyElements();
	}

	return (*this);
}

Container &Container::Update()
{
	for (auto i = packages.begin(); i != packages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->Update();
	}
	return (*this);
}

Container &Container::ToSend()
{
	for (auto i = packages.begin(); i != packages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->ToSend();
	}

	return (*this);
}

Container &Container::ApplyBuffer()
{
	for (auto i = packages.begin(); i != packages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->ApplyBuffer();
	}

	return (*this);
}
