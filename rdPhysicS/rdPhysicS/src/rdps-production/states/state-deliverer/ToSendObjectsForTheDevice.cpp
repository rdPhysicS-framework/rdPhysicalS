#include "ToSendObjectsForTheDevice.h"
#include "..\..\collaborators\ObjectDispatcher.h"

USING_RDPS
USING_PDCT

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
}

void ToSendObjectsForTheDevice::Exit(const ObjectDispatcher &c)
{
}

bool ToSendObjectsForTheDevice::OnMessage(const ObjectDispatcher &c, const Message &msg)
{
	return false;
}
