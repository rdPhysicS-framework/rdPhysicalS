#include "LogError.h"
#include "../Application/ClConfig.h"

USING_RDPS

rdps::LogError::LogError(const std::string &message) :
	std::exception(message.c_str())
{}

rdps::LogError::LogError(const char *message) :
	std::exception(message)
{}

void Logger::GetErrorPlatformComponent(const int error, std::string msg)
{
	if (error == CL_INVALID_VALUE)
		msg += "CL_INVALID_VALUE: any of the parameters may be wrong.";
}

void Logger::GetErrorDeviceComponent(const int error, std::string msg)
{
	switch (error)
	{
	case CL_INVALID_PLATFORM: 
		msg += "CL_INVALID_PLATFORM: invalid informed platform.";
		break;
	case CL_INVALID_DEVICE_TYPE: 
		msg += "CL_INVALID_PLATFORM: invalid device_type";
		break;
	case CL_INVALID_VALUE: 
		msg += "CL_INVALID_PLATFORM: num_entries can be zero or device_type is not NULL or both num_devices and device_type are NULL.";
		break;
	case CL_DEVICE_NOT_FOUND: 
		msg += "CL_INVALID_PLATFORM: CL_DEVICE_NOT_FOUND no OpenCL device matches the type of device found.";
		break;
	}
}

void Logger::GetErrorContextComponent(const int error, std::string msg)
{
	switch (error)
	{
	case CL_INVALID_PLATFORM:
		msg += "CL_INVALID_PLATFORM: invalid patafroma or device is NULL or num_devices is equal to zero.";
		break;
	case CL_INVALID_VALUE:
		msg += "CL_INVALID_DEVICE: devices may contain an invalid device or is not associated with the specified platform.";
		break;
	case CL_DEVICE_NOT_AVAILABLE:
		break;
	case CL_OUT_OF_HOST_MEMORY:
		msg += "CL_OUT_OF_HOST_MEMORY: failed to allocate the resources required by the OpenCL implementation on the host.";
		break;
	}
}

void Logger::Log(const std::string message)
{
	throw LogError(message);
}

void Logger::Log(const int error, const std::string message)
{
	GetErrorPlatformComponent(error, message);
	GetErrorDeviceComponent(error, message);

	throw LogError(message);
}
