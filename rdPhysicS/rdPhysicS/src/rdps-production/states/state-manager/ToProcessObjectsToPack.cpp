#include "ToProcessObjectsToPack.h"
#include "..\..\..\rdps-packages\input\Container.h"
#include "..\..\collaborators\ObjectDispatcher.h"
#include "..\..\msg\MessageDispatcher.h"
#include "..\..\msg\Message.h"
#include "..\..\collaborators\GeneralManager.h"
#include "..\..\collaborators\ManagerObjects.h"
#include "..\state-global\ToRest.h"
#include "..\StateMachine.h"

USING_RDPS
USING_PDCT

State<ManagerObjects> *ToProcessObjectsToPack::INSTANCE = nullptr;

ToProcessObjectsToPack::ToProcessObjectsToPack()
{
}

ToProcessObjectsToPack::~ToProcessObjectsToPack()
{
}

State<ManagerObjects>* ToProcessObjectsToPack::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToProcessObjectsToPack();
	return INSTANCE;
}

void ToProcessObjectsToPack::Enter(const ManagerObjects &c)
{
}

void ToProcessObjectsToPack::Execute(const ManagerObjects &c)
{
	c.GetStateMachine()->ChangeState(ToRest::Get());
}

void ToProcessObjectsToPack::Exit(const ManagerObjects &c)
{
	MessageDispatcher::DispatchMessage((Entity*)&c, GeneralManager::Get(), "concluded");
}

bool ToProcessObjectsToPack::OnMessage(const ManagerObjects &c, const Message &msg)
{
	if (msg.GetMessage() == "request")
	{
		MessageDispatcher::DispatchMessage((Collaborator*)&c, GeneralManager::Get(), "executing");
		return true;
	}
	return false;
}
