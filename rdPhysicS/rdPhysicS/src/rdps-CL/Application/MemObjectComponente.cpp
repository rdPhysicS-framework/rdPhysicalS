#include "MemObjectComponente.h"
#include "ContextComponente.h"
#include "../Util/LogError.h"

USING_RDPS
USING_CL

MemObjectComponente::MemObjectComponente() :
					 BaseClComponente<Type>()
{}

MemObjectComponente::MemObjectComponente(const ContextComponente &context,
										 const  ActionFile typeAction,
										 const size_t size               ) :
					 BaseClComponente<Type>(Create(context, typeAction, size))
{}

MemObjectComponente::MemObjectComponente(const cl_mem &memObj) :
					 BaseClComponente<Type>(memObj)
{}

MemObjectComponente::MemObjectComponente(const MemObjectComponente &other) :
					 BaseClComponente<Type>(other)
{}

MemObjectComponente::~MemObjectComponente()
{
	Release();
}

void MemObjectComponente::Release()
{
	if (object)
	{
		if (int status = clReleaseMemObject(object) !=
			CL_SUCCESS)
			Logger::Log("clReleaseMemObject - Error when destroying the" 
						"memory object. ERROR: " + std::to_string(status));

		object = nullptr;
	}
}

void MemObjectComponente::Retain()
{
	if (object)
	{
		if (int status = clRetainMemObject(object) !=
			CL_SUCCESS)
			Logger::Log("clRetainMemObject - ERROR: " + std::to_string(status));
	}
}

cl_mem MemObjectComponente::Create(const ContextComponente &context, 
								   const  ActionFile typeAction,
								   const size_t size)
{
	int status = 0;
	Type mem = clCreateBuffer(context(), typeAction, size, nullptr, &status);
	/*tratar erro*/
	return mem;
}
