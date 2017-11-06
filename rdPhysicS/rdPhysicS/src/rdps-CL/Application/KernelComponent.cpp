#include "KernelComponent.h"
#include "DeviceComponent.h"
#include "ProgramComponent.h"
#include "..\..\Util\Details.h"

USING_RDPS
USING_CL

cl_kernel KernelComponent::Create(const ProgramComponent &program, 
								  const std::string &name)
{
	int status = 0;
	cl_kernel kernel = clCreateKernel(program(), name.c_str(), &status);
	if (status != CL_SUCCESS)
	{
		Logger::Log("ERROR when creating the kernel function.");
	}

	return kernel;
}

KernelComponent::KernelComponent() :
		  BaseClComponent<Type>()
{
}

KernelComponent::KernelComponent(const ProgramComponent &program,
								 const std::string &name         ) :
	      BaseClComponent<Type>(Create(program, name))
{}

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
			Logger::Log("ERROR when destroying the kernel.");
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
			Logger::Log("clRetainKernel ERROR: " + std::to_string(status));
		}
	}
}

std::string KernelComponent::GetInfo(const cl_kernel_info paramName)
{
	return Details::DisplayKernelInfo(*this, paramName);
}

size_t *KernelComponent::GetKernelWorkGroupInfo(const DeviceComponent &device, 
											    const cl_kernel_work_group_info paramName)
{
	return Details::DisplayKernelWorkGroupInfo(*this, device, paramName);
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
