#include "CommandQueueComponente.h"
#include "ContextComponente.h"
#include "DeviceComponente.h"
#include "ItensWorkGroupComponente.h"
#include "KernelComponente.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL


CommmandQueueComponente::CommmandQueueComponente() :
						 BaseClComponente<Type>()
{}

CommmandQueueComponente::CommmandQueueComponente(const ContextComponente &context,
														 const DeviceComponente  &device  ) :
						 BaseClComponente<Type>()
{
	int status;
	object = clCreateCommandQueue(context(), device(), 0, &status);
	/*importante tratar erro*/
}

CommmandQueueComponente::CommmandQueueComponente(const cl_command_queue &queue) :
						 BaseClComponente<Type>(queue)
{}

CommmandQueueComponente::CommmandQueueComponente(const CommmandQueueComponente &other) :
						 BaseClComponente<Type>(other)
{}

CommmandQueueComponente::~CommmandQueueComponente()
{
	Release();
}

void CommmandQueueComponente::Release()
{
	if (object)
	{
		if (int status = clReleaseCommandQueue(object) != CL_SUCCESS)
		{
			throw std::out_of_range("ERROR: " + std::to_string(status));
		}

		object = nullptr;
	}
}

void CommmandQueueComponente::Retain()
{
	if (object)
	{
		if (int status = clRetainCommandQueue(object) != CL_SUCCESS)
		{
			Logger::Log("ERROR: " + std::to_string(status));
		}
	}
}

std::string CommmandQueueComponente::GetInfo(const cl_command_queue_info paramName)
{
	return std::string();
}

CommmandQueueComponente 
	&CommmandQueueComponente::EnqueueNDRangeKernel(const KernelComponente &kernel, 
															const ItensWorkGroupComponente &itens)
{
	/*adicionar o kernel para funcionar*/
	if (int status = clEnqueueNDRangeKernel(object, kernel(), itens.GetDimensions(), 
											itens.GetOffSet(), itens.GetGlobalItens(), 
											itens.GetLocalItens(), 0, nullptr, nullptr) != CL_SUCCESS)
	{
		Logger::Log("ERROR: " + std::to_string(status));
	}

	return (*this);
}

CommmandQueueComponente 
	&CommmandQueueComponente::EnqueueTask(const KernelComponente &kernel)
{
	/*adicionar o kernel para funcionar*/
	if (int status = clEnqueueTask(object, kernel(), 0, nullptr, nullptr)) 
	{
		/****Inportante Tratar erro ****/
	}

	return (*this);
}

