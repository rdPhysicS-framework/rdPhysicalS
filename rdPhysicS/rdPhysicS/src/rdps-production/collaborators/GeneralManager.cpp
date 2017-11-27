#include "GeneralManager.h"
#include "..\..\Util\LogError.h"
#include "..\states\StateMachine.h"
#include "..\msg\MessageDispatcher.h"
#include "..\msg\Message.h"
#include "..\base\Collaborator.h"
#include "ManagerObjects.h"
#include "ObjectDispatcher.h"
#include "PackerObjects.h"
#include "..\Util\ObjectsHostPkg.h"

USING_RDPS
USING_PDCT

GeneralManager *GeneralManager::INSTANCE = nullptr;

GeneralManager::GeneralManager()
{}

GeneralManager::GeneralManager(const GeneralManager &other) :
				collaborators(other.collaborators)
{}

GeneralManager::~GeneralManager()
{}

GeneralManager *GeneralManager::Get()
{
	if (!INSTANCE)
		INSTANCE = new GeneralManager();

	return INSTANCE;
}
const Collaborator * GeneralManager::GetCollaborator(const CollaboratorsFunction function)
{
	return collaborators[function];
}

const std::map<CollaboratorsFunction, Collaborator*> &GeneralManager::GetCollaborators() const
{
	return collaborators;
}

GeneralManager &GeneralManager::AddCollaborator(CollaboratorsFunction function,
												Collaborator *collaborator)
{
	if (collaborators.find(function) != collaborators.end())
	{
		Logger::Log("Busy place - (id collaborator)");
	}

	collaborators[function] = collaborator;
	return (*this);
}

GeneralManager &GeneralManager::RemoveCollaborator(CollaboratorsFunction function)
{
	if (collaborators.find(function) == collaborators.end())
	{
		Logger::Log("Collaborator doesn't exist");
	}

	collaborators.erase(function);
}

//GeneralManager *GeneralManager::Clone()
//{
//	return new GeneralManager(*this);
//}

GeneralManager &GeneralManager::ExecuteFunction()
{
	collaborators[MANAGER_OF_OBJECTS]->ExecuteFunction();
	collaborators[PACKER_OF_OBJECTS]->ExecuteFunction();
	collaborators[DELIVERER_OF_OBJECTS]->ExecuteFunction();

	return (*this);
}

bool GeneralManager::HandleMessage(const Message &message)
{
	if (!message.GetSender() && message.GetMessage() == "request")
	{
		MessageDispatcher::DispatchMessage(this, 
										   collaborators[MANAGER_OF_OBJECTS],
										   message.GetMessage());
		return true;
	}
	else if (message.GetMessage() == "concluded")
	{
		if (((Collaborator*)message.GetSender())->GetFunction() == MANAGER_OF_OBJECTS)
		{
			MessageDispatcher::DispatchMessage(this,
											   collaborators[PACKER_OF_OBJECTS],
											   "to pack");
			return true;
		}
		else if (((Collaborator*)message.GetSender())->GetFunction() == PACKER_OF_OBJECTS)
		{
			MessageDispatcher::DispatchMessage(this, 
											   collaborators[DELIVERER_OF_OBJECTS],
											   "to send");
			return true;
		}
		else if (((Collaborator*)message.GetSender())->GetFunction() == DELIVERER_OF_OBJECTS)
		{
			return true;
		}

	}
	else if (message.GetMessage() == "executing")
	{
		if (((Collaborator*)message.GetSender())->GetFunction() == MANAGER_OF_OBJECTS)
		{
			return true;
		}
		else if (((Collaborator*)message.GetSender())->GetFunction() == PACKER_OF_OBJECTS)
		{
			return true;
		}
		else if (((Collaborator*)message.GetSender())->GetFunction() == DELIVERER_OF_OBJECTS)
		{
			return true;
		}

	}
	return false;
}
