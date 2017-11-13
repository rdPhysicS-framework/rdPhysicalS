#include "ToPackObjectsForDevice.h"
#include "..\..\collaborators\PackerObjects.h"

USING_RDPS
USING_PDCT

State<PackerObjects> *ToPackObjectsForDevice::INSTANCE = nullptr;

ToPackObjectsForDevice::ToPackObjectsForDevice()
{}

ToPackObjectsForDevice::~ToPackObjectsForDevice()
{}

State<PackerObjects>* ToPackObjectsForDevice::Get()
{
	if (!INSTANCE)
		INSTANCE = new ToPackObjectsForDevice();
	return INSTANCE;
}

void ToPackObjectsForDevice::Enter(const PackerObjects &c)
{
}

void ToPackObjectsForDevice::Execute(const PackerObjects &c)
{
}

void ToPackObjectsForDevice::Exit(const PackerObjects &c)
{
}

bool ToPackObjectsForDevice::OnMessage(const PackerObjects & f, const Message & msg)
{
	return false;
}
