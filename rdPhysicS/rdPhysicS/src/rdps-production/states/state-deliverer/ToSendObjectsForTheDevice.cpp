#include "ToSendObjectsForTheDevice.h"
#include "..\..\..\rdps-packages\input\Container.h"
#include "..\..\collaborators\ObjectDispatcher.h"
#include "..\..\msg\MessageDispatcher.h"
#include "..\..\msg\Message.h"
#include "..\..\collaborators\GeneralManager.h"
#include "..\StateMachine.h"
#include "..\state-global\ToRest.h"
#include "..\..\..\rdps-packages\input\Package.h"
#include "..\..\..\rdps-packages\output\Renderer.h"

USING_RDPS
USING_PDCT
USING_PKG

State<ObjectDispatcher> *ToSendObjectsForTheDevice::INSTANCE = nullptr;

ToSendObjectsForTheDevice::ToSendObjectsForTheDevice()
{}

ToSendObjectsForTheDevice::~ToSendObjectsForTheDevice()
{}

State<ObjectDispatcher> *ToSendObjectsForTheDevice::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToSendObjectsForTheDevice();
	return INSTANCE;
}

void ToSendObjectsForTheDevice::Enter(const ObjectDispatcher &c)
{
}

void ToSendObjectsForTheDevice::Execute(const ObjectDispatcher &c)
{
	Container *container = c.GetContainer();
	container->Update();
	World::GetRenderer()->Update();
	container->ApplyBuffer();
	//container->ToSend();
	//World::GetRenderer()->GetBuffer()->ToSend();

	const Package<RT_Primitive> *aux = dynamic_cast<const Package<RT_Primitive>*>(container->GetPackage("objects"));
	for (int i = 0; i < aux->elements.size(); i++)
	{
		Logger::TestPrim(aux->elements[i]);
		std::cout << std::endl;
	}

	c.GetStateMachine()->ChangeState(ToRest::Get());
}

void ToSendObjectsForTheDevice::Exit(const ObjectDispatcher &c)
{
	MessageDispatcher::DispatchMessage((Entity*)&c, GeneralManager::Get(), "concluded");
}

bool ToSendObjectsForTheDevice::OnMessage(const ObjectDispatcher &c, const Message &msg)
{
	if (msg.GetMessage() == "to send")
	{
		MessageDispatcher::DispatchMessage((Collaborator*)&c, GeneralManager::Get(), "executing");
		return true;
	}

	return false;
}
