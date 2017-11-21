#include "ToRest.h"
#include "..\..\base\Collaborator.h"
#include "..\..\msg\MessageDispatcher.h"
#include "..\..\msg\Message.h"
#include "..\..\base\Collaborator.h"
#include "..\..\states\StateMachine.h"
#include "..\..\states\state-packer\ToPackObjectsForDevice.h"
#include "..\..\states\state-deliverer\ToSendObjectsForTheDevice.h"
#include "..\..\states\state-manager\ToProcessObjectsToPack.h"

USING_RDPS
USING_PDCT

State<Collaborator> *ToRest::INSTANCE = nullptr;

ToRest::ToRest()
{}

ToRest::~ToRest()
{}

State<Collaborator>* ToRest::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToRest();
	return INSTANCE;
}

void ToRest::Enter(const Collaborator &c)
{
}

void ToRest::Execute(const Collaborator &c)
{
}

void ToRest::Exit(const Collaborator &c)
{
}

bool ToRest::OnMessage(const Collaborator &c, const Message &msg)
{
	if (msg.GetMessage() == "to pack")
	{
		if (c.GetFunction() == PACKER_OF_OBJECTS)
		{
			c.GetStateMachine()->ChangeState((State<Collaborator>*)(ToPackObjectsForDevice::Get()));
			return true;
		}
		return false;
	}
	else if (msg.GetMessage() == "to send")
	{
		if (c.GetFunction() == DELIVERER_OF_OBJECTS)
		{
			c.GetStateMachine()->ChangeState((State<Collaborator>*)(ToSendObjectsForTheDevice::Get()));
			return true;
		}
		return false;
	}
	else if (msg.GetMessage() == "request")
	{
		if (c.GetFunction() == MANAGER_OF_OBJECTS)
		{
			c.GetStateMachine()->ChangeState((State<Collaborator>*)(ToProcessObjectsToPack::Get()));
			return true;
		}
		return false;
	}
	return false;
}
