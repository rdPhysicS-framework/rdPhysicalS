#include "ApplicationCLBuider.h"
#include "ApplicationCL.h"
#include "PlatformComponent.h"
#include "DeviceComponent.h"
#include "ItensWorkGroupComponent.h"
#include "..\..\Util\UtilGlobalDef.h"

USING_RDPS
USING_CL

ApplicationCLBuilder::ApplicationCLBuilder() :
					  app(new ApplicationCL())
{}

ApplicationCLBuilder::~ApplicationCLBuilder()
{}

ApplicationCLBuilder &ApplicationCLBuilder::AddPlatform(const PlatformComponent &platform)
{
	app->SetPlatform(platform);
	return (*this);
}

ApplicationCLBuilder &ApplicationCLBuilder::AddDevice(const DeviceComponent &device)
{
	app->SetDevice(device);
	return (*this);
}

ApplicationCLBuilder &ApplicationCLBuilder::AddItensWorkGroup(const ItensWorkGroupComponent &itens)
{
	app->SetItensWorkGroup(itens);
	return (*this);
}

ApplicationCLBuilder &ApplicationCLBuilder::AddFunctionKernel(const std::string &name)
{
	app->CreateKernel(name);
	return (*this);
}

ApplicationCLBuilder &ApplicationCLBuilder::LoadProgram(const std::initializer_list<std::string> &files)
{
	std::string code = LoaderFiles::LoadSource(files);
	app->CreateProgram(code);
	return (*this);
}
