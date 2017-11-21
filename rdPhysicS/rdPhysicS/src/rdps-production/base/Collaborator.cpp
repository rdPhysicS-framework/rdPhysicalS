#include "Collaborator.h"
#include "..\states\StateMachine.h"

USING_RDPS
USING_PDCT

Collaborator::Collaborator(const CollaboratorsFunction _function,
						   StateMachine *_stateMachine) :
			  function(_function),
			  stateMachine(_stateMachine)
{}

Collaborator::Collaborator(const Collaborator &other) :
			  function(other.function),
			  stateMachine(other.stateMachine->Clone())
{}

Collaborator::~Collaborator()
{
	if (stateMachine)
		delete stateMachine;
}

const CollaboratorsFunction Collaborator::GetFunction() const
{
	return function;
}

StateMachine *Collaborator::GetStateMachine() const
{
	return stateMachine;
}

bool Collaborator::HandleMessage(const Message &message)
{
	return stateMachine->HandleMessage(message);
}
