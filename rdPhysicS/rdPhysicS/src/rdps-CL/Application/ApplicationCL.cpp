#include "ApplicationCL.h"
#include "PlatformComponent.h"
#include "DeviceComponent.h"
#include "ContextComponent.h"
#include "CommandQueueComponent.h"
#include "ProgramComponent.h"
#include "KernelComponent.h"
#include "MemObjectComponent.h"
#include "ItensWorkGroupComponent.h"

USING_RDPS
USING_CL

ApplicationCL::ApplicationCL() :
			   platform(nullptr), 
			   device(nullptr),
			   context(nullptr),
			   queue(nullptr),
			   program(nullptr),
			   kernel(nullptr),
			   itens(nullptr)
{}

ApplicationCL::ApplicationCL(const PlatformComponent &_platform, 
							 const DeviceComponent   &_device   ) :
			   platform(new PlatformComponent(_platform)), 
			   device(new DeviceComponent(_device)), 
			   context(nullptr),
			   queue(nullptr), 
			   program(nullptr), 
			   kernel(nullptr), 
			   itens(nullptr)
{}

inline ApplicationCL &ApplicationCL::CreateContext()
{ 
	context = new ContextComponent(*device);
	return (*this);
}

inline ApplicationCL &ApplicationCL::CreateCommandQueue()
{
	queue = new CommmandQueueComponent(*context, *device);
	return (*this);
}

ApplicationCL::~ApplicationCL()
{
	if(program)
		delete program;
	if(device)
		delete device;
	if(context)
		delete context;
	if(queue)
		delete queue;
	if(kernel)
		delete kernel;

	for (auto i : buffers)
		i->Release();
	buffers.clear();
}

ApplicationCL &ApplicationCL::CreateProgram(const std::string &source)
{
	CreateContext();
	CreateCommandQueue();
	program = new ProgramComponent(*context, source);
	program->BuildProgram(*device);
	return (*this);
}

ApplicationCL &ApplicationCL::CreateKernel(const std::string &name)
{
	kernel = new KernelComponent(*program, name);
	return (*this);
}

int ApplicationCL::CreateBuffer(const int id, const ActionFile typeAction, const size_t bytes)
{
	if (id <= ARRAY_WITHOUT_INDEX)
	{
		MemObjectComponent *mem = new MemObjectComponent(*context, typeAction, bytes);
		buffers.push_back(mem);
		return static_cast<int>(buffers.size() - 1);
	}

	int _id = GetBuffer(id);
	if (_id == EMPTY_BUFFER || _id == BUSY_LOCATION)
	{
		Logger::Log((_id == EMPTY_BUFFER) ?
			"ERROR: list of objects of memory empty.\n" :
			"ERROR requested index invalidates busy location.\n");
	}

	*buffers[_id] = MemObjectComponent(*context, typeAction, bytes);

	return id;
}

std::string ApplicationCL::GetInfo(const ComponentCL type) const
{
	switch (type)
	{
	case PLATFORM_COMPONENT:
		return platform->GetInfo(CL_PLATFORM_NAME);
		break;
	case DEVICE_COMPONENT:
		return device->GetInfo(CL_DEVICE_NAME);
		break;
	case CONTEXT_COMPONENT:

		break;
	case COMMAND_QUEUE_COMPONENT:

		break;
	case PROGRAM_COMPONENT:

		break;
	case KERNEL_COMPONENT:

		break;
	case ALL_COMPONENTS:

		break;
	}

	return std::string();
}

int ApplicationCL::GetBuffer()
{
	buffers.push_back(new MemObjectComponent());
	return static_cast<int>(buffers.size() - 1);
}

int ApplicationCL::GetBuffer(const int location)
{
	if (buffers.size() == 0)
		return EMPTY_BUFFER;

	if ((*buffers[location])())
		return BUSY_LOCATION;

	return location;
}

ApplicationCL &ApplicationCL::SetPlatform(const PlatformComponent &_platform)
{
	if (!platform)
	{
		platform = new PlatformComponent(_platform);
	}
	else
	{
		*platform = _platform;
	}
	return (*this);
}

ApplicationCL &ApplicationCL::SetDevice(const DeviceComponent &_device)
{
	if (!device)
	{
		device = new DeviceComponent(_device);
	}
	else
	{
		*device = _device;
	}
	return (*this);
}

ApplicationCL &ApplicationCL::SetItensWorkGroup(const ItensWorkGroupComponent &_itens)
{
	if (!itens)
	{
		itens = new ItensWorkGroupComponent(_itens);
	}
	else
	{
		*itens = _itens;
	}

	return (*this);
}

void rdps::Cl::ApplicationCL::DestroyBuffer(const int id)
{
	if (buffers.size() > 0)
		if ((*buffers[id])())
			buffers[id]->Release();
}

void ApplicationCL::DestroyApp()
{
	kernel->Release();
	program->Release();

	for (auto i : buffers)
	{
		i->Release();
		delete i;
	}
	buffers.clear();

	queue->Release();
	context->Release();
}

ApplicationCL &ApplicationCL::ApplyArgument(const int id)
{
	kernel->SetArgument(id, (*buffers[id])());
	return (*this);
}

ApplicationCL &ApplicationCL::ApplyArguments()
{
	int size = static_cast<int>(buffers.size());
	for (int i = 0; i < size; i++)
		kernel->SetArgument(i, (*buffers[i])());
	return(*this);
}

ApplicationCL &ApplicationCL::ApplyArguments(const std::initializer_list<uint> index)
{
	std::vector<uint> ids = index;
	for (auto i : ids)
		kernel->SetArgument(i, (*buffers[i])());
	return (*this);
}

ApplicationCL &ApplicationCL::ApplyBuffer(const int id, const ActionFile typeAction, const size_t bytes, void * data)
{
	if (typeAction == RETURN_DATA_WRITING)
	{
		int _id = id;// GetBuffer(bf.GetId());
		if (_id == EMPTY_BUFFER || _id == BUSY_LOCATION)
		{
			Logger::Log("ERROR requested index invalidates " +
				(_id == EMPTY_BUFFER) ? "empty array." : "busy location.");
		}

		queue->WriteBuffer((*buffers[_id]), bytes, data);
	}
	else if (typeAction == RETURN_DATA_READING)
	{
		int _id = id;//GetBuffer(bf.GetId());
		if (_id == EMPTY_BUFFER || id == BUSY_LOCATION)
		{
			Logger::Log("ERROR requested index invalidates " +
				(_id == EMPTY_BUFFER) ? "empty array." : "busy location.");
		}

		queue->ReadBuffer((*buffers[_id]), bytes, data);
	}

	return (*this);
}

ApplicationCL &ApplicationCL::Process(const bool applyEverything)
{
	if (applyEverything)
		ApplyArguments();
	queue->EnqueueNDRangeKernel(*kernel, *itens);

	return (*this);
}


