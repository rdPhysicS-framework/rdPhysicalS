#include "ContextComponent.h"
#include "DeviceComponent.h"

USING_RDPS
USING_CL

ContextComponent::ContextComponent() :
				   BaseClComponent<Type>()
{}

ContextComponent::ContextComponent(const DeviceComponent &device ,
											 const cl_context_properties *prop) :
				   BaseClComponent<Type>()
{
	cl_device_id id = device();
	int status = 0;
	object = clCreateContext(prop, 1, &id, nullptr, nullptr, &status);
	/*tratar erro*/
}

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
			throw std::out_of_range("ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void ContextComponent::Retain()
{
	if (object)
	{
		int status = clRetainContext(object);
		if (status != CL_SUCCESS)
			throw std::out_of_range("ERROR: " + std::to_string(status));
	}
}

std::string ContextComponent::GetInfo(const cl_context_info paramName)
{
	return std::string();
}
