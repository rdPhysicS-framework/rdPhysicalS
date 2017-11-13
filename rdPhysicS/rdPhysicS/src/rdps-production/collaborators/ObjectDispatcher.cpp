#include "ObjectDispatcher.h"

USING_RDPS
USING_PDCT

ObjectDispatcher::ObjectDispatcher() :
	Collaborator(DELIVERER_OF_OBJECTS),
	container(nullptr)
{}

ObjectDispatcher::ObjectDispatcher(const ObjectDispatcher &other) :
	Collaborator(other),
	container(other.container)
{}

ObjectDispatcher::~ObjectDispatcher()
{}

Collaborator *ObjectDispatcher::Clone()
{
	return new ObjectDispatcher(*this);
}

Collaborator &ObjectDispatcher::Init()
{
	return (*this);
}

Collaborator &ObjectDispatcher::ExecuteFunction()
{
	return (*this);
}

Collaborator &ObjectDispatcher::Exit()
{
	return (*this);
}

bool ObjectDispatcher::HandleMessage(const Message & message)
{
	return false;
}
