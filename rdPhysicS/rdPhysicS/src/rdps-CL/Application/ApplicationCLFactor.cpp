#include "ApplicationCLFactor.h"
#include "../ClGlobalDef.h"
#include <iostream>

USING_RDPS
USING_CL

uint ApplicationCLFactor::GetOptions(uint size)
{
	if (size == 1)
		return 0;

	uint input = 1;

	std::cout << "Choice one of the options!" << std::endl
			  << "Option: ";
	std::cin >> input;

	while (input < 1 || input > size)
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		std::cout << "No such option. Choose again!" 
				  << std::endl 
				  << "nOption: ";
		std::cin >> input;
	}

	return (input - 1);
}

ApplicationCL *ApplicationCLFactor::CreateApplicationUsersInput()
{
	std::vector<PlatformComponent> platforms = PlatformComponent::GetPlatforms();
	
	uint size = static_cast<uint>(platforms.size());

	for (uint i = 0; i < size; i++)
	{
		std::cout << (i+1) << " - Platform Name: "
				  << platforms[i]
				     .GetInfo(CL_PLATFORM_NAME) 
				  << std::endl;
	}

	std::cout << std::endl;
	uint p = GetOptions(size);

	std::vector<DeviceComponent> devices = platforms[p].GetDevices(CL_DEVICE_TYPE_ALL);

	size = static_cast<uint>(devices.size());
	
	for (uint i = 0; i < size; i++)
	{	
		std::cout << "\t"
				  << (i+1) << " - Device Name: "
				  << devices[i]
				     .GetInfo(CL_DEVICE_NAME)
				  <<std::endl
				  << "\t    Device Max Compute Units: "
				  << devices[i]
					 .GetInfo(CL_DEVICE_MAX_COMPUTE_UNITS)
				 << std::endl
				  << "\t    Device Max Work Group Size: "
				  << devices[i]
					 .GetInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE)
				  << std::endl;
	}

	uint d = GetOptions(size);

	return ApplicationCLBuilder()
				.AddPlatform(platforms[p])
				.AddDevice(devices[d])
				.LoadProgram({CLPATH"rtUtil.cl",
							  CLPATH"rtStructs.cl" ,
							  CLPATH"rtMaterial.cl" ,
							  CLPATH"rtGeometricObject.cl" ,
							  CLPATH"rtLights.cl" ,
							  CLPATH"rtWorld.cl",
							  CLPATH"rtKernel.cl"})
				.AddFunctionKernel("test")
				.AddItensWorkGroup(ItensWorkGroupComponent({1}))
				.Create();
}
