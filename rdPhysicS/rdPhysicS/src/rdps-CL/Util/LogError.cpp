#include "LogError.h"
#include "../Application/ClConfig.h"

rdps::LogError::LogError(const std::string &message) :
	std::exception(message.c_str())
{}

rdps::LogError::LogError(const char *message) :
	std::exception(message)
{}

std::string rdps::Logger::GetErrorMessage(const InfoComponentCL componenet,
										  const int codeError)
{
	switch (componenet)
	{
	case PLATFORM_COMPONENT:
		return GetErrorPlatformComponent(codeError);
	case DEVICE_COMPONENT:
		return GetErrorDeviceComponent(codeError);
	case CONTEXT_COMPONENT:
		return GetErrorContextComponent(codeError);
	case COMMAND_QUEUE_COMPONENT:
		return GetErrorCommandQueueInfo(codeError);
	case PROGRAM_COMPONENT:
	case KERNEL_COMPONENT:
	case PLATFORM_COMPONENT_INFO:
		return GetErrorPlatformInfo(codeError);
	case DEVICE_COMPONENT_INFO:
		return GetErrorPlatformInfo(codeError);
	case CONTEXT_COMPONENT_INFO:
		return GetErrorContextInfo(codeError);
	case COMMAND_QUEUE_COMPONENT_INFO:
		return GetErrorCommandQueueInfo(codeError);
	case PROGRAM_COMPONENT_INFO:
	case KERNEL_COMPONENT_INFO:
		break;
	}

	throw LogError("code of the error or information of the invalid component.");
}

std::string rdps::Logger::GetErrorPlatformComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_VALUE:
		return PLATFORM_INVALID_VALUE;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorPlatformInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return INVALID_PLATFORM;
	case CL_INVALID_VALUE:
		return INVALID_VALUE;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorDeviceComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return INVALID_PLATFORM;
	case CL_INVALID_DEVICE_TYPE:
		return INVALID_DEVICE_TYPE;
	case CL_INVALID_VALUE:
		return INVALID_VALUE;
	case CL_DEVICE_NOT_FOUND:
		return DEVICE_NOT_FOUND;
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorDeviceInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_DEVICE:
		return INVALID_DEVICE;
	case CL_INVALID_VALUE:
		return INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}

	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorContextComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return "CL_INVALID_PLATFORM: invalid patafroma or device is NULL or num_devices is equal to zero.";
	case CL_INVALID_PROPERTY:
		return "CL_INVALID_VALUE: the invalid context property name.";
	case CL_INVALID_VALUE:
		return "CL_INVALID_VALUE: the invalid context property name; or devices is NULL;"
			   "or num_devices is equal to zero; or if pfn_notify is NULL, or user_data is not NULL.";
	case CL_INVALID_DEVICE:
		return "CL_INVALID_DEVICE: devices may contain an invalid device or is not associated with the specified platform.";
	case CL_DEVICE_NOT_AVAILABLE:
		return "CL_DEVICE_NOT_AVAILABLE: device is currently not available.";
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorContextInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_CONTEXT:
		return INVALID_CONTEXT;
	case CL_INVALID_VALUE:
		return INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorCommandQueueComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_CONTEXT:
		return INVALID_CONTEXT;
	case CL_INVALID_DEVICE:
		return INVALID_DEVICE;
	case CL_INVALID_VALUE:
		return QUEUE_INVALID_VALUE;
	case CL_INVALID_QUEUE_PROPERTIES:
		return INVALID_QUEUE_PROPERTIES;
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}

	return EMPTY_ERROR_MESSAGE;
}

std::string rdps::Logger::GetErrorCommandQueueInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_COMMAND_QUEUE:
		return INVALID_COMMAND_QUEUE;
	case CL_INVALID_VALUE:
		return QUEUE_INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return HOST_MEMORY;
	}
	return EMPTY_ERROR_MESSAGE;
}

void rdps::Logger::Log(const std::string message)
{
	throw LogError(message);
}

void rdps::Logger::Log(const InfoComponentCL componenet, const int codeError, const std::string message)
{
}
