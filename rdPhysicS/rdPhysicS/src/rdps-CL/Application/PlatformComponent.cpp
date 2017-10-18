#include "PlatformComponent.h"
#include "DeviceComponent.h"
#include "../Util/Details.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL

PlatformComponent::PlatformComponent() : 
					BaseClComponent<Type>()
{}

PlatformComponent::PlatformComponent(const cl_platform_id &_id) :
					BaseClComponent<Type>(_id)
{}

PlatformComponent::PlatformComponent(const PlatformComponent &other) :
					BaseClComponent<Type>(other)
{}

PlatformComponent::~PlatformComponent()
{}

std::string PlatformComponent::GetInfo(const cl_platform_info paramName)
{
	return Details::DisplayPlatformInfo(object, paramName);
}

std::vector<PlatformComponent> PlatformComponent::GetPlatforms()
{
	cl_uint size = 0;
	cl_int status = clGetPlatformIDs(0, nullptr, &size);
	if (status != CL_SUCCESS)
		Logger::Log("Unable to verify the platforms. ERROR: "
					+ std::to_string(status));

	cl_platform_id *p = new cl_platform_id[size];
	status = clGetPlatformIDs(size, p, nullptr);
	if (status != CL_SUCCESS)
		Logger::Log("Unable to capture the platforms. ERROR: "
					+ std::to_string(status));

	return std::vector<PlatformComponent>(&p[0], &p[size]);
}

std::vector<DeviceComponent> PlatformComponent::GetDevices(const cl_device_type type)
{
	cl_uint size = 0;
	cl_int status = clGetDeviceIDs(object, type, 0, nullptr, &size);
	if (status != CL_SUCCESS)
		Logger::Log("Unable to verify the devices. ERROR: "
					+ std::to_string(status));

	cl_device_id *d = new cl_device_id[size];
	status = clGetDeviceIDs(object, type, size, d, nullptr);
	if (status != CL_SUCCESS)
		Logger::Log("Unable to capture the devices. ERROR: "
					+ std::to_string(status));

	return std::vector<DeviceComponent>(&d[0], &d[size]);
}
