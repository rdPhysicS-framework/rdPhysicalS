#include "MemObjectComponent.h"
#include "ContextComponent.h"
#include "..\..\Util\LogError.h"

USING_RDPS
USING_CL

MemObjectComponent::MemObjectComponent() :
					 BaseClComponent<Type>()
{}

MemObjectComponent::MemObjectComponent(const ContextComponent &context,
										 const  ActionFile typeAction,
										 const size_t size               ) :
					 BaseClComponent<Type>(Create(context, typeAction, size))
{}

MemObjectComponent::MemObjectComponent(const cl_mem &memObj) :
					 BaseClComponent<Type>(memObj)
{}

MemObjectComponent::MemObjectComponent(const MemObjectComponent &other) :
					 BaseClComponent<Type>(other)
{}

MemObjectComponent::~MemObjectComponent()
{
	//Release();
}

void MemObjectComponent::Release()
{
	if (object)
	{
		int status = clReleaseMemObject(object);

		if (status != CL_SUCCESS)
			Logger::Log("clReleaseMemObject - Error when destroying the" 
						"memory object. ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void MemObjectComponent::Retain()
{
	if (object)
	{
		int status = clRetainMemObject(object);

		if (status != CL_SUCCESS)
			Logger::Log("clRetainMemObject - ERROR: " + std::to_string(status));
	}
}

cl_mem MemObjectComponent::Create(const ContextComponent &context, 
								  const  ActionFile typeAction,
								  const size_t size)
{
	int status = 0;
	cl_mem mem = clCreateBuffer(context(), typeAction, size, nullptr, &status);
	if (status != CL_SUCCESS)
	{
		Logger::Log("ERROR when creating the memory object.\n");
	}
	return mem;
}

MemObjectComponent &MemObjectComponent::operator=(const MemObjectComponent &other)
{
	if (this != &other)
		BaseClComponent<Type>::operator=(other);
	return (*this);
}
