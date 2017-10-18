#include "ApplicationRT.h"

USING_RDPS
USING_CL
USING_PKG

ApplicationRT::ApplicationRT() :
			   platform(nullptr), 
			   device(),
			   context(),
			   queue(), 
			   program(), 
			   kernel(), 
			   itens({})
{}

ApplicationRT::ApplicationRT(const PlatformComponent &_platform, 
							 const DeviceComponent   &_device   ) :
			   platform(_platform), 
			   device(_device), 
			   context(),
			   queue(), 
			   program(), 
			   kernel(), 
			   itens({})
{}

inline ApplicationRT &ApplicationRT::CreateContext()
{ 
	context = ContextComponent(device);
	return (*this);
}

inline ApplicationRT &ApplicationRT::CreateCommandQueue()
{
	queue = CommmandQueueComponent(context, device);
	return (*this);
}

ApplicationRT::~ApplicationRT()
{}

ApplicationRT &ApplicationRT::CreateProgram(const std::string &source)
{
	CreateContext();
	CreateCommandQueue();
	program = ProgramComponent(context, source);
	program.BuildProgram(device);
	return (*this);
}

ApplicationRT &ApplicationRT::CreateKernel(const std::string &name)
{
	kernel = KernelComponent(program, name);
	return (*this);
}

std::string ApplicationRT::GetInfo(const InfoComponentCL type) const
{
	switch (type)
	{
	case PLATFORM_COMPONENT:
		
		break;
	case DEVICE_COMPONENT:

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
	buffers.push_back(MemObjectComponent());
	return buffers.size() - 1;
}

int ApplicationRT::GetBuffer(const int location)
{
	if (!buffers.data())
		return EMPTY_BUFFER;

	if (buffers[location]())
		return BUSY_LOCATION;

	return location;
}

ApplicationRT &ApplicationRT::SetPlatform(const PlatformComponent &_platform)
{
	platform = _platform;
	return (*this);
}

ApplicationRT &ApplicationRT::SetDevice(const DeviceComponent &_device)
{
	device = _device;
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
		if (buffers[id]())
			buffers[id].Release();
}

void ApplicationRT::DestroyApp()
{
	kernel.Release();
	program.Release();

	for (auto i : buffers)
		i.Release();
	buffers.clear();

	queue.Release();
	context.Release();
}

ApplicationRT &ApplicationRT::ApplyArgument(const int id)
{
	kernel.SetArgument(id, buffers[id]());
	return (*this);
}

ApplicationRT &ApplicationRT::ApplyArguments()
{
	int size = buffers.size();
	for (int i = 0; i < size; i++)
		kernel.SetArgument(i, buffers[i]());
	return(*this);
}

ApplicationRT &ApplicationRT::ApplyArguments(const std::initializer_list<uint> index)
{
	std::vector<uint> ids = index;
	for (auto i : ids)
		kernel.SetArgument(i, buffers[i]());
	return (*this);
}

ApplicationRT &ApplicationRT::Process(const bool applyEverything)
{
	if (applyEverything)
		ApplyArguments();
	queue.EnqueueNDRangeKernel(kernel, itens);
}


