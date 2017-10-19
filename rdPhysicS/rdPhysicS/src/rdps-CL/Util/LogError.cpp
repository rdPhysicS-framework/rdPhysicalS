#include "LogError.h"
#include "../Application/ClConfig.h"

USING_RDPS

LogError::LogError(const std::string &message) :
	  std::exception(message.c_str())
{}

rdps::LogError::LogError(const char *message) :
	  std::exception(message)
{}

char *Logger::GetErrorMessage(const InfoComponentCL componenet,
										  const int codeError)
{
	switch (componenet)
	{
	case PLATFORM_COMPONENT_CREATE:
		return GetErrorPlatformComponent(codeError);
	case DEVICE_COMPONENT_CREATE:
		return GetErrorDeviceComponent(codeError);
	case CONTEXT_COMPONENT_CREATE:
		return GetErrorContextComponent(codeError);
	case COMMAND_QUEUE_COMPONENT_CREATE:
		return GetErrorCommandQueueInfo(codeError);
	case PROGRAM_COMPONENT_CREATE:
	case KERNEL_COMPONENT_CREATE:
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

	throw LogError("Information of the invalid component.");
}

char *Logger::GetErrorPlatformComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_VALUE:
		return ERROR_MSG_PLATFORM_INVALID_VALUE;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorPlatformInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return ERROR_MSG_INVALID_PLATFORM;
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorDeviceComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return ERROR_MSG_INVALID_PLATFORM;
	case CL_INVALID_DEVICE_TYPE:
		return ERROR_MSG_INVALID_DEVICE_TYPE;
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_DEVICE_NOT_FOUND:
		return ERROR_MSG_DEVICE_NOT_FOUND;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorDeviceInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_DEVICE:
		return ERROR_MSG_INVALID_DEVICE;
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorContextComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_PLATFORM:
		return ERROR_MSG_INVALID_PLATFORM_DEVICE;
	case CL_INVALID_PROPERTY:
		return ERROR_MSG_INVALID_PROPERTY;
	case CL_INVALID_VALUE:
		return ERROR_MSG_CONTEXT_INVALID_VALUE;
	case CL_INVALID_DEVICE:
		return ERROR_MSG_CONTEXT_INVALID_DEVICE;
	case CL_DEVICE_NOT_AVAILABLE:
		return ERROR_MSG_DEVICE_NOT_AVAILABLE;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorContextInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_CONTEXT:
		return ERROR_MSG_INVALID_CONTEXT;
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}
	
	throw LogError("Invalid error code.");
}

char *Logger::GetErrorCommandQueueComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_CONTEXT:
		return ERROR_MSG_INVALID_CONTEXT;
	case CL_INVALID_DEVICE:
		return ERROR_MSG_INVALID_DEVICE;
	case CL_INVALID_VALUE:
		return ERROR_MSG_QUEUE_INVALID_VALUE;
	case CL_INVALID_QUEUE_PROPERTIES:
		return ERROR_MSG_INVALID_QUEUE_PROPERTIES;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorCommandQueueInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_COMMAND_QUEUE:
		return ERROR_MSG_INVALID_COMMAND_QUEUE;
	case CL_INVALID_VALUE:
		return ERROR_MSG_QUEUE_INVALID_VALUE;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}

	throw LogError("Invalid error code.");
}

char *Logger::GetErrorProgramComponent(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_CONTEXT:
		return ERROR_MSG_INVALID_CONTEXT;
	case CL_INVALID_VALUE:
		return ERROR_MSG_PROGRAM_INVALID_VALUE;
	case CL_INVALID_DEVICE:
		return ERROR_MSG_INVALID_DEVICE_CONTEXT;
	case CL_INVALID_BINARY:
		return ERROR_MSG_INVALID_BYNARY;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}
	throw LogError("Invalid error code.");
}

char *Logger::GetErrorProgramInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_INVALID_PROGRAM:
		return ERROR_MSG_INVALID_PROGRAM;
	case CL_INVALID_DEVICE:
		return ERROR_MSG_INVALID_DEVICE_CONTEXT;
	case CL_INVALID_PROGRAM_EXECUTABLE:
		return ERROR_MSG_INVALID_PROGRAM_EXECUTABLE;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}
	throw LogError("Invalid error code.");
}

char *Logger::GetErrorProgramBuildInfo(const int codeError)
{
	switch (codeError)
	{
	case CL_INVALID_DEVICE:
		return ERROR_MSG_INVALID_DEVICE_PROGRAM;
	case CL_INVALID_VALUE:
		return ERROR_MSG_INVALID_VALUE;
	case CL_INVALID_PROGRAM:
		return ERROR_MSG_INVALID_PROGRAM;
	case CL_OUT_OF_RESOURCES:
		return ERROR_MSG_OUT_OF_RESOURCES;
	case CL_OUT_OF_HOST_MEMORY:
		return ERROR_MSG_HOST_MEMORY;
	}
	throw LogError("Invalid error code.");
}

void Logger::Log(const std::string message)
{
	throw LogError(message);
}

void Logger::Log(const InfoComponentCL componenet, const int codeError, const std::string message)
{
	throw LogError(message + "\n" + GetErrorMessage(componenet, codeError));
}
