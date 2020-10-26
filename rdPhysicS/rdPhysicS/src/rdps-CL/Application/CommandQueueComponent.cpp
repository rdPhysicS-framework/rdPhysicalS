#include "CommandQueueComponent.h"
#include "ContextComponent.h"
#include "DeviceComponent.h"
#include "ItensWorkGroupComponent.h"
#include "KernelComponent.h"

USING_RDPS
USING_CL

cl_command_queue CommmandQueueComponent::Create(const ContextComponent &context, 
												const DeviceComponent &device)
{
	int status;
	cl_command_queue queue = clCreateCommandQueue(context(), device(), 0, &status);
	if (status != CL_SUCCESS)
		Logger::Log(COMMAND_QUEUE_COMPONENT_CREATE, status, 
					"Error when creating the command_queue.");

	return queue;
}

CommmandQueueComponent::CommmandQueueComponent() :
						 BaseClComponent<Type>()
{}

CommmandQueueComponent::CommmandQueueComponent(const ContextComponent &context,
											   const DeviceComponent  &device  ) :
						 BaseClComponent<Type>(Create(context, device))
{}

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
		int status = clReleaseCommandQueue(object);
		if (status != CL_SUCCESS)
		{
			Logger::Log("clReleaseCommandQueue:"
						"Erro ao destruir a fila de comando.\nERROR: " 
						+ std::to_string(status));
		}

		object = nullptr;
	}
}

void CommmandQueueComponent::Retain()
{
	if (object)
	{
		int status = clRetainCommandQueue(object);

		if (status != CL_SUCCESS)
		{
			Logger::Log("clRetainCommandQueue ERROR: " + std::to_string(status));
		}
	}
}

std::string CommmandQueueComponent::GetInfo(const cl_command_queue_info paramName)
{
	return std::string();
}

CommmandQueueComponent &CommmandQueueComponent::ReadBuffer(const MemObjectComponent &memObj, const size_t size, void *data)
{
	int status = clEnqueueReadBuffer(object, memObj(), CL_TRUE,
									 0, size, data,
									 0, nullptr, nullptr);
	if (status != CL_SUCCESS)
	{
		Logger::Log("ERROR when writing the data in the buffer."
					"\nERROR: " + std::to_string(status));
	}
	return (*this);
}

CommmandQueueComponent &CommmandQueueComponent::WriteBuffer(const MemObjectComponent &memObj, const size_t size, void *data)
{
	if (memObj())
	{
		int status = clEnqueueWriteBuffer(object, memObj(), CL_TRUE,
										  0, size, (const void*)data,
										  0, nullptr, nullptr);

		if (status != CL_SUCCESS)
		{
			Logger::Log("clEnqueueWriteBuffer ERROR: " + std::to_string(status));
		}
	}

	return (*this);
}

CommmandQueueComponent 
	&CommmandQueueComponent::EnqueueNDRangeKernel(const KernelComponent &kernel, 
												  const ItensWorkGroupComponent &itens)
{
	int status = clEnqueueNDRangeKernel(object, kernel(), itens.GetDimensions(),
										itens.GetOffSet(), itens.GetGlobalItens(),
										itens.GetLocalItens(), 0, nullptr, nullptr);
	if ( status != CL_SUCCESS)
	{
		Logger::Log("Error when processing the data for parallel data.\nERROR: " + std::to_string(status));
	}

	return (*this);
}

CommmandQueueComponent 
	&CommmandQueueComponent::EnqueueTask(const KernelComponent &kernel)
{
	cl_int status = clEnqueueTask(object, kernel(), 0, nullptr, nullptr);

	if (status != CL_SUCCESS) 
	{
		/****Inportante Tratar erro ****/
		Logger::Log("Error when processing the data for parallel task.\nERROR: " + std::to_string(status));
	}

	return (*this);
}

CommmandQueueComponent &CommmandQueueComponent::operator=(const CommmandQueueComponent & other)
{
	if (this != &other)
		BaseClComponent<Type>::operator=(other);
	return (*this);
}

