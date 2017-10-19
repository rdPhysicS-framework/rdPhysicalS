#include "ApplicationRT.h"

USING_RDPS
USING_CL
USING_PKG

ApplicationRT::ApplicationRT() :
			   platform(nullptr), 
			   device(nullptr),
			   context(nullptr),
			   queue(nullptr),
			   program(nullptr),
			   kernel(nullptr),
			   itens({})
{}

ApplicationRT::ApplicationRT(const PlatformComponent &_platform, 
							 const DeviceComponent   &_device   ) :
			   platform(new PlatformComponent(_platform)), 
			   device(new DeviceComponent(_device)), 
			   context(),
			   queue(), 
			   program(), 
			   kernel(), 
			   itens({})
{}

inline ApplicationRT &ApplicationRT::CreateContext()
{ 
	context = new ContextComponent(*device);
	return (*this);
}

inline ApplicationRT &ApplicationRT::CreateCommandQueue()
{
	queue = new CommmandQueueComponent(*context, *device);
	return (*this);
}

ApplicationRT::~ApplicationRT()
{
	delete program;
	delete device;
	delete context;
	delete queue;
	delete kernel;
	for (auto i : buffers)
		i->Release();
	buffers.clear();
}

ApplicationRT &ApplicationRT::CreateProgram(const std::string &source)
{
	CreateContext();
	CreateCommandQueue();
	program = new ProgramComponent(*context, source);
	program->BuildProgram(*device);
	return (*this);
}

ApplicationRT &ApplicationRT::CreateKernel(const std::string &name)
{
	kernel = new KernelComponent(*program, name);
	return (*this);
}

std::string ApplicationRT::GetInfo(const ComponentCL type) const
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

int ApplicationRT::GetBuffer()
{
	buffers.push_back(new MemObjectComponent());
	return static_cast<int>(buffers.size() - 1);
}

int ApplicationRT::GetBuffer(const int location)
{
	if (buffers.size() == 0)
		return EMPTY_BUFFER;

	if ((*buffers[location])())
		return BUSY_LOCATION;

	return location;
}

ApplicationRT &ApplicationRT::SetPlatform(const PlatformComponent &_platform)
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

ApplicationRT &ApplicationRT::SetDevice(const DeviceComponent &_device)
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

ApplicationRT &ApplicationRT::SetItensWorkGroup(const ItensWorkGroupComponent &_itens)
{
	itens = _itens;
	return (*this);
}

void rdps::Cl::ApplicationRT::DestroyBuffer(const int id)
{
	if (buffers.size() > 0)
		if ((*buffers[id])())
			buffers[id]->Release();
}

void ApplicationRT::DestroyApp()
{
	kernel->Release();
	program->Release();

	for (auto i : buffers)
		i->Release();
	buffers.clear();

	queue->Release();
	context->Release();
}

ApplicationRT &ApplicationRT::ApplyArgument(const int id)
{
	kernel->SetArgument(id, (*buffers[id])());
	return (*this);
}

ApplicationRT &ApplicationRT::ApplyArguments()
{
	int size = static_cast<int>(buffers.size());
	for (int i = 0; i < size; i++)
		kernel->SetArgument(i, (*buffers[i])());
	return(*this);
}

ApplicationRT &ApplicationRT::ApplyArguments(const std::initializer_list<uint> index)
{
	std::vector<uint> ids = index;
	for (auto i : ids)
		kernel->SetArgument(i, (*buffers[i])());
	return (*this);
}

ApplicationRT &ApplicationRT::Process(const bool applyEverything)
{
	if (applyEverything)
		ApplyArguments();
	queue->EnqueueNDRangeKernel(*kernel, itens);

	return (*this);
}


