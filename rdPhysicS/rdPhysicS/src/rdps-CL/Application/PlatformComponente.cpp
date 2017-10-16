#include "PlatformComponente.h"
#include "DeviceComponente.h"
#include "../Util/Details.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL

PlatformComponente::PlatformComponente() : 
					BaseClComponente<Type>()
{}

PlatformComponente::PlatformComponente(const cl_platform_id &_id) :
					BaseClComponente<Type>(_id)
{}

PlatformComponente::PlatformComponente(const PlatformComponente &other) :
					BaseClComponente<Type>(other)
{}

PlatformComponente::~PlatformComponente()
{}

std::string PlatformComponente::GetInfo(const cl_platform_info paramName)
{
	return Details::DisplayPlatformInfo(object, paramName);
}

std::vector<PlatformComponente> PlatformComponente::GetPlatforms()
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

	return std::vector<PlatformComponente>(&p[0], &p[size]);
}

std::vector<DeviceComponente> PlatformComponente::GetDevices(const cl_device_type type)
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

	return std::vector<DeviceComponente>(&d[0], &d[size]);
}
