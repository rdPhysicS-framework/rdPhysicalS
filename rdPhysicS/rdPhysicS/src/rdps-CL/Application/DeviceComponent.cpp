#include "DeviceComponent.h"
#include "..\..\Util\Details.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_CL

DeviceComponent::DeviceComponent() :
				  BaseClComponent<Type>()
{}

DeviceComponent::DeviceComponent(const cl_device_id &device) :
				  BaseClComponent<Type>(device)
{}

DeviceComponent::DeviceComponent(const DeviceComponent & other) :
				  BaseClComponent<Type>(other)
{}

DeviceComponent::~DeviceComponent()
{
	//Release();
}

void DeviceComponent::Release()
{
	if (object)
	{
		int status = clReleaseDevice(object);
		if (status != CL_SUCCESS)
			Logger::Log("clReleaseDevice ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void DeviceComponent::Retain()
{
	if (object)
	{
		int status = clRetainDevice(object);
		if (status != CL_SUCCESS)
			Logger::Log("clRetainDevice ERROR: " + std::to_string(status));
	}
}

std::string DeviceComponent::GetInfo(const cl_device_info paramName)
{
	return Details::DisplayDeviceDetails(object, paramName);
}

DeviceComponent &DeviceComponent::operator=(const DeviceComponent &other)
{
	if (this != &other)
		object = other.object;
	return (*this);
}
