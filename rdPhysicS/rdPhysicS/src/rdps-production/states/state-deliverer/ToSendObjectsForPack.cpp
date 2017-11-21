#include "ToSendObjectsForPack.h"
#include "..\..\collaborators\ObjectDispatcher.h"
#include "..\..\msg\MessageDispatcher.h"
#include "..\..\msg\Message.h"
#include "..\..\collaborators\GeneralManager.h"

USING_RDPS
USING_PDCT

State<ObjectDispatcher>* ToSendObjectsForPack::INSTANCE = nullptr;

ToSendObjectsForPack::ToSendObjectsForPack()
{}

ToSendObjectsForPack::~ToSendObjectsForPack()
{}

State<ObjectDispatcher>* ToSendObjectsForPack::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToSendObjectsForPack();
	return INSTANCE;
}

void ToSendObjectsForPack::Enter(const ObjectDispatcher &c)
{
}

void ToSendObjectsForPack::Execute(const ObjectDispatcher &c)
{
}

void ToSendObjectsForPack::Exit(const ObjectDispatcher &c)
{
	MessageDispatcher::DispatchMessage((Entity*)&c, GeneralManager::Get(), "concluded");
}

bool ToSendObjectsForPack::OnMessage(const ObjectDispatcher &c, const Message & msg)
{
	return false;
}
