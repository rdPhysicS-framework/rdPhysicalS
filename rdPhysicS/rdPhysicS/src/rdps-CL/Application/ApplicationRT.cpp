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

ApplicationRT::ApplicationRT(const PlatformComponente &_platform, 
							 const DeviceComponente   &_device   ) :
			   platform(_platform), 
			   device(_device), 
			   context(),
			   queue(), 
			   program(), 
			   kernel(), 
			   itens({})
{}

ApplicationRT::~ApplicationRT()
{}

ApplicationRT &ApplicationRT::CreateProgram(const std::string &source)
{
	CreateContext();
	CreateCommandQueue();
	program = ProgramComponente(context, source);
	program.BuildProgram(device);
	return (*this);
}

ApplicationRT &ApplicationRT::CreateKernel(const std::string &name)
{
	kernel = KernelComponente(program, name);
	return (*this);
}

std::string ApplicationRT::GetInfo(const InfoComponenteCL type) const
{
	switch (type)
	{
	case PLATFORM_COMPOENETE:
		
		break;
	case DEVICE_COMPONENTE:

		break;
	case CONTEXT_COMPONENETE:

		break;
	case COMMAND_QUEUE_COMPONENETE:

		break;
	case PROGRAM_COMPONENETE:

		break;
	case KERNEL_COMPONENETE:

		break;
	case ALL_COMPONENTES:

		break;
	}

	return std::string();
}

int ApplicationRT::GetBuffer()
{
	buffers.push_back(MemObjectComponente());
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

ApplicationRT &ApplicationRT::SetPlatform(const PlatformComponente &_platform)
{
	platform = _platform;
	return (*this);
}

ApplicationRT &ApplicationRT::SetDevice(const DeviceComponente &_device)
{
	device = _device;
	return (*this);
}

ApplicationRT &ApplicationRT::SetItensWorkGroup(const ItensWorkGroupComponente &_itens)
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

void ApplicationRT::Process(const bool applyEverything)
{
	if (applyEverything)
		ApplyArguments();
	queue.EnqueueNDRangeKernel(kernel, itens);
}


