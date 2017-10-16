#include "ContextComponente.h"
#include "DeviceComponente.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL

ContextComponente::ContextComponente() :
				   BaseClComponente<Type>()
{}

ContextComponente::ContextComponente(const DeviceComponente &device ,
									 const cl_context_properties *prop) :
				   BaseClComponente<Type>()
{
	cl_device_id id = device();
	int status = 0;
	object = clCreateContext(prop, 1, &id, nullptr, nullptr, &status);
	/*tratar erro*/
}

ContextComponente::ContextComponente(const cl_context &context) :
				   BaseClComponente<Type>(context)
{}

ContextComponente::ContextComponente(const ContextComponente &other) :
				   BaseClComponente<Type>(other)
{}

ContextComponente::~ContextComponente()
{
	Release();
}

void ContextComponente::Release()
{
	if (object)
	{
		int status = clReleaseContext(object);
		if (status != CL_SUCCESS)
			Logger::Log("ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void ContextComponente::Retain()
{
	if (object)
	{
		int status = clRetainContext(object);
		if (status != CL_SUCCESS)
			Logger::Log("ERROR: " + std::to_string(status));
	}
}

std::string ContextComponente::GetInfo(const cl_context_info paramName)
{
	return std::string();
}
