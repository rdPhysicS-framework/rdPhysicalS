#include "KernelComponent.h"
#include "DeviceComponent.h"
#include "ProgramComponent.h"
#include "../Util/Details.h"

USING_RDPS
USING_CL

KernelComponent::KernelComponent() :
		  BaseClComponent<Type>()
{
}

KernelComponent::KernelComponent(const ProgramComponent &program, 
										   const std::string &name            ) :
	      BaseClComponent<Type>()
{
	int status = 0;
	object = clCreateKernel(program(), name.c_str(), &status);
	/*Importante tratar erro*/
}

KernelComponent::KernelComponent(const cl_kernel &kernel) :
		  BaseClComponent<Type>(kernel)
{}

KernelComponent::KernelComponent(const KernelComponent &other) :
		  BaseClComponent<Type>(other)
{}

KernelComponent::~KernelComponent()
{
	Release();
}

void KernelComponent::Release()
{
	if (object)
	{
		if (int status = clReleaseKernel(object) !=
			CL_SUCCESS)
		{
			/*Tratar erro*/
		}

		object = nullptr;
	}
}

void KernelComponent::Retain()
{
	if (object)
	{
		if (int status = clRetainKernel(object) !=
			CL_SUCCESS)
		{
			/*Tratar erro*/
		}
	}
}

std::string KernelComponent::GetInfo(const cl_kernel_info paramName)
{
	return std::string();
}

std::string KernelComponent::GetInfo(const DeviceComponent &device, const cl_kernel_work_group_info paramName)
{
	return Details::DisplayDeviceDetails(device(), paramName);
}

KernelComponent &KernelComponent::SetArgument(int index, const void *data, const size_t bytes)
{
	if (int status = clSetKernelArg(object, index, bytes, data))
	{
		Logger::Log("ERROR when setting the argument " + std::to_string(index)
			+ "\nERROR: " + std::to_string(status));

	}

	return (*this);
}
