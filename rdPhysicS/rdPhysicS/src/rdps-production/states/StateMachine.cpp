#include "StateMachine.h"
#include "..\base\Collaborator.h"
#include "..\msg\Message.h"
#include "..\base\State.h"

USING_RDPS
USING_PDCT

StateMachine::StateMachine(Collaborator *owner) :
			  myOwner(owner),
			  currentState(nullptr),
			  previousState(nullptr),
			  globalState(nullptr)
{}

StateMachine::StateMachine(const StateMachine &other) :
			  myOwner(other.myOwner->Clone()),
			  currentState(other.currentState),
			  previousState(other.previousState),
			  globalState(other.globalState)
{}

StateMachine::~StateMachine()
{}

StateMachine *StateMachine::Clone() const
{
	return new StateMachine(*this);
}

StateMachine &StateMachine::operator=(const StateMachine &other)
{
	*myOwner = *other.myOwner;
	currentState = other.currentState;
	previousState = other.previousState;
	globalState = other.globalState;
	return (*this);
}

Collaborator *StateMachine::GetOwner() const
{
	return myOwner;
}

State<Collaborator> *StateMachine::GetCurrentState() const
{
	return currentState;
}

State<Collaborator> *StateMachine::GetPreviousState() const
{
	return previousState;
}

State<Collaborator>* StateMachine::GetGlobalState() const
{
	return globalState;
}

StateMachine &StateMachine::SetCurrentState(State<Collaborator> *_currentState)
{
	currentState = _currentState;
	return (*this);
}

StateMachine &StateMachine::SetPreviousState(State<Collaborator> *_previousState)
{
	previousState = _previousState;
	return (*this);
}

StateMachine &StateMachine::SetGlobalState(State<Collaborator> *_globalState)
{
	globalState = _globalState;
	return (*this);
}

StateMachine &StateMachine::Update()
{
	if (globalState)
		globalState->Execute(*myOwner);

	if (currentState)
		currentState->Execute(*myOwner);

	return (*this);
}

StateMachine &StateMachine::ChangeState(State<Collaborator> *newState)
{
	if (!previousState &&
		!currentState)
	{
		previousState = newState;
		currentState = newState;
	}

	previousState = currentState;

	currentState->Exit(*myOwner);

	currentState = newState;
	currentState->Enter(*myOwner);

	return (*this);
}

StateMachine &StateMachine::ReverToPreviousState()
{
	return ChangeState(previousState);
}

bool StateMachine::HandleMessage(const Message &message)
{
	return (currentState && currentState->OnMessage(*myOwner, message)) ||
		   (globalState  && globalState->OnMessage(*myOwner, message));
}
