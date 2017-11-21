#include "ObjectDispatcher.h"
#include "..\states\StateMachine.h"
#include "..\states\state-global\ToRest.h"
#include "..\..\rdps-packages\input\Container.h"

USING_RDPS
USING_PDCT
USING_PKG

ObjectDispatcher::ObjectDispatcher(PKG Container *_container) :
				  Collaborator(DELIVERER_OF_OBJECTS, 
				  			   new StateMachine(this)),
				  container(_container)
{
	stateMachine->SetCurrentState(ToRest::Get());
}

ObjectDispatcher::ObjectDispatcher(const ObjectDispatcher &other) :
	Collaborator(other),
	container(other.container)
{}

ObjectDispatcher::~ObjectDispatcher()
{}

PKG Container *ObjectDispatcher::GetContainer() const
{
	return container;
}

Collaborator *ObjectDispatcher::Clone()
{
	return new ObjectDispatcher(*this);
}

Collaborator &ObjectDispatcher::Init()
{
	stateMachine->GetCurrentState()->Enter(*this);
	return (*this);
}

Collaborator &ObjectDispatcher::ExecuteFunction()
{
	stateMachine->Update();
	return (*this);
}

Collaborator &ObjectDispatcher::Exit()
{
	stateMachine->GetCurrentState()->Exit(*this);
	return (*this);
}
