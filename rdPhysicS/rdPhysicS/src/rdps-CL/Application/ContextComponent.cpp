#include "ContextComponent.h"
#include "DeviceComponent.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_CL

cl_context ContextComponent::Create(const DeviceComponent &device, const cl_context_properties *prop)
{
	cl_device_id id = device();
	int status = 0;
	cl_context context = clCreateContext(prop, 1, &id, nullptr, nullptr, &status);

	if (status != CL_SUCCESS)
		Logger::Log(CONTEXT_COMPONENT_CREATE, status, "Error when creating the context OpenCL.");

	return context;
}

ContextComponent::ContextComponent() :
				   BaseClComponent<Type>()
{}

ContextComponent::ContextComponent(const DeviceComponent &device ,
								   const cl_context_properties *prop) :
				   BaseClComponent<Type>(Create(device, prop))
{}

ContextComponent::ContextComponent(const cl_context &context) :
				   BaseClComponent<Type>(context)
{}

ContextComponent::ContextComponent(const ContextComponent &other) :
				   BaseClComponent<Type>(other)
{}

ContextComponent::~ContextComponent()
{
	Release();
}

void ContextComponent::Release()
{
	if (object)
	{
		int status = clReleaseContext(object);
		if (status != CL_SUCCESS)
			Logger::Log("clReleaseContext ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void ContextComponent::Retain()
{
	if (object)
	{
		int status = clRetainContext(object);
		if (status != CL_SUCCESS)
			Logger::Log("clRetainContext ERROR: " + std::to_string(status));
	}
}

std::string ContextComponent::GetInfo(const cl_context_info paramName)
{
	return std::string();
}

ContextComponent &ContextComponent::operator=(const ContextComponent &other)
{
	if (this != &other)
		BaseClComponent<Type>::operator=(other);
	return (*this);
}
