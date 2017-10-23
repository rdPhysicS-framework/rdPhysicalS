#include "Container.h"
#include "base\PackageBase.h"
#include "..\..\rdps-CL\Util\LogError.h"

USING_RDPS
USING_PKG

Container::Container()
{}

Container::~Container()
{
	for (auto i = pakages.begin(); i != pakages.end(); ++i)
	{
		delete i->second;
	}
	pakages.clear();
}

Container &Container::CreatePackage(std::string id, 
								    PackageBase *package)
{
	if (pakages.find(id) != pakages.end())
	{
		Logger::Log("Busy place - id: " + id);
	}
	
	pakages[id] = package;
	
	return (*this);
}

Container &Container::RemoveElement(std::string id, const int element)
{
	pakages[id]->RemoveElement(element);
	return (*this);
}

Container &Container::DestroyElements(std::string id)
{
	pakages[id]->DestroyElements();
	return (*this);
}

Container &Container::DestroyElements()
{
	for (auto i = pakages.begin(); i != pakages.end(); ++i)
	{
		i->second->DestroyElements();
	}

	return (*this);
}

Container &Container::Update()
{
	for (auto i = pakages.begin(); i != pakages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->Update();
	}
	return (*this);
}

Container &Container::ToSend()
{
	for (auto i = pakages.begin(); i != pakages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->ToSend();
	}

	return (*this);
}

Container &Container::ApplyBuffer()
{
	for (auto i = pakages.begin(); i != pakages.end(); ++i)
	{
		PackageBase *p = i->second;
		p->ApplyBuffer();
	}

	return (*this);
}
