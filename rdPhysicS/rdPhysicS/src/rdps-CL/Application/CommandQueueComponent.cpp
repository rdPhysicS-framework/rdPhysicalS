#include "CommandQueueComponent.h"
#include "ContextComponent.h"
#include "DeviceComponent.h"
#include "ItensWorkGroupComponent.h"
#include "KernelComponent.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL


CommmandQueueComponent::CommmandQueueComponent() :
						 BaseClComponent<Type>()
{}

CommmandQueueComponent::CommmandQueueComponent(const ContextComponent &context,
														 const DeviceComponent  &device  ) :
						 BaseClComponent<Type>()
{
	int status;
	object = clCreateCommandQueue(context(), device(), 0, &status);
	/*importante tratar erro*/
}

CommmandQueueComponent::CommmandQueueComponent(const cl_command_queue &queue) :
						 BaseClComponent<Type>(queue)
{}

CommmandQueueComponent::CommmandQueueComponent(const CommmandQueueComponent &other) :
						 BaseClComponent<Type>(other)
{}

CommmandQueueComponent::~CommmandQueueComponent()
{
	Release();
}

void CommmandQueueComponent::Release()
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

void CommmandQueueComponent::Retain()
{
	if (object)
	{
		if (int status = clRetainCommandQueue(object) != CL_SUCCESS)
		{
			Logger::Log("ERROR: " + std::to_string(status));
		}
	}
}

std::string CommmandQueueComponent::GetInfo(const cl_command_queue_info paramName)
{
	return std::string();
}

CommmandQueueComponent 
	&CommmandQueueComponent::EnqueueNDRangeKernel(const KernelComponent &kernel, 
															const ItensWorkGroupComponent &itens)
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

CommmandQueueComponent 
	&CommmandQueueComponent::EnqueueTask(const KernelComponent &kernel)
{
	/*adicionar o kernel para funcionar*/
	if (int status = clEnqueueTask(object, kernel(), 0, nullptr, nullptr)) 
	{
		/****Inportante Tratar erro ****/
	}

	return (*this);
}

