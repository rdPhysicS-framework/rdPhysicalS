#include "ApplicationRTBuider.h"
#include "ApplicationRT.h"
#include "PlatformComponente.h"
#include "DeviceComponente.h"
#include "ItensWorkGroupComponente.h"
#include "../Util/UtilGlobalDef.h"

USING_RDPS
USING_CL

ApplicationRTBuilder::ApplicationRTBuilder() :
					  app(new ApplicationRT())
{}

ApplicationRTBuilder::~ApplicationRTBuilder()
{}

ApplicationRTBuilder &ApplicationRTBuilder::AddPlatform(const PlatformComponente &platform)
{
	app->SetPlatform(platform);
	return (*this);
}

ApplicationRTBuilder &ApplicationRTBuilder::AddDevice(const DeviceComponente &device)
{
	app->SetDevice(device);
	return (*this);
}

ApplicationRTBuilder &ApplicationRTBuilder::AddItensWorkGroup(const ItensWorkGroupComponente &itens)
{
	app->SetItensWorkGroup(itens);
	return (*this);
}

ApplicationRTBuilder &ApplicationRTBuilder::AddFunctionKernel(const std::string &name)
{
	app->CreateKernel(name);
	return (*this);
}

ApplicationRTBuilder &ApplicationRTBuilder::LoadProgram(const std::initializer_list<std::string> files)
{
	std::string code = LoaderFiles::LoadSource(files);
	app->CreateProgram(code);
	return (*this);
}
