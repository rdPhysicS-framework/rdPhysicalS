#include "DeviceComponente.h"
#include "../Util/Details.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL

DeviceComponente::DeviceComponente() :
				  BaseClComponente<Type>()
{}

DeviceComponente::DeviceComponente(const cl_device_id &device) :
				  BaseClComponente<Type>(device)
{}

DeviceComponente::DeviceComponente(const DeviceComponente & other) :
				  BaseClComponente<Type>(other)
{}

DeviceComponente::~DeviceComponente()
{
	//Release();
}

void DeviceComponente::Release()
{
	if (object)
	{
		int status = clReleaseDevice(object);
		if (status != CL_SUCCESS)
			Logger::Log("ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void DeviceComponente::Retain()
{
	if (object)
	{
		int status = clRetainDevice(object);
		if (status != CL_SUCCESS)
			Logger::Log("ERROR: " + std::to_string(status));
	}
}

std::string DeviceComponente::GetInfo(const cl_device_info paramName)
{
	return Details::DisplayDeviceDetails(object, paramName);
}
