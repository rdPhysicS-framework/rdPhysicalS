#include "MessageDispatcher.h"
#include "Message.h"
#include "..\base\Entity.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_PDCT

void MessageDispatcher::DeliverMessage(Entity *receiver, 
									   const Message &message)
{
	if (!receiver->HandleMessage(message))
		Logger::Log("Entity can't treat the message");
}

void MessageDispatcher::DispatchMessage(Entity *sender, 
										Entity *receiver, 
										const std::string message, 
										void *data)
{
	DeliverMessage(receiver, Message(sender, receiver, message, data));
}


