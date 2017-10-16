#include "KernelComponente.h"
#include "DeviceComponente.h"
#include "ProgramComponente.h"
#include "../Util/Details.h"

USING_RDPS
USING_CL

KernelComponente::KernelComponente() :
		  BaseClComponente<Type>()
{
}

KernelComponente::KernelComponente(const ProgramComponente &program, 
										   const std::string &name            ) :
	      BaseClComponente<Type>()
{
	int status = 0;
	object = clCreateKernel(program(), name.c_str(), &status);
	/*Importante tratar erro*/
}

KernelComponente::KernelComponente(const cl_kernel &kernel) :
		  BaseClComponente<Type>(kernel)
{}

KernelComponente::KernelComponente(const KernelComponente &other) :
		  BaseClComponente<Type>(other)
{}

KernelComponente::~KernelComponente()
{
	Release();
}

void KernelComponente::Release()
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

void KernelComponente::Retain()
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

std::string KernelComponente::GetInfo(const cl_kernel_info paramName)
{
	return std::string();
}

std::string KernelComponente::GetInfo(const DeviceComponente &device, const cl_kernel_work_group_info paramName)
{
	return Details::DisplayDeviceDetails(device(), paramName);
}

KernelComponente &KernelComponente::SetArgument(int index, const void *data, const size_t bytes)
{
	if (int status = clSetKernelArg(object, index, bytes, data))
	{
		Logger::Log("ERROR when setting the argument " + std::to_string(index)
			+ "\nERROR: " + std::to_string(status));

	}

	return (*this);
}
