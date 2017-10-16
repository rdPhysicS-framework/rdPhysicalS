#include "Dispositive.h"
#include "../Util/Details.h"

rdps::Cl::Dispositive::Dispositive(cl_platform_id platform, 
								   cl_device_id device     ):
	platform(platform),
	device(device)
{}

std::string rdps::Cl::Dispositive::GetPlatformInfo(cl_platform_info name)
{
	return (platform) ? Details::DisplayPlatformInfo(platform, name) :
						throw std::exception("Impossible of it verifies "
										     "the details. Platform is null!");
}

std::string rdps::Cl::Dispositive::GetDeviceInfo(cl_device_info name)
{
	return (device) ? Details::DisplayDeviceDetails(device, name) :
					  throw std::exception("Impossible of it verifies "
										   "the details. device is null!");
}

std::string rdps::Cl::Dispositive::GetInfo()
{
	try
	{
		std::string info = "CL_PLATFORM_NAME: " + GetPlatformInfo(CL_PLATFORM_NAME) + "\n\n" +
						   "CL_PLATFORM_VENDOR: " + GetPlatformInfo(CL_PLATFORM_VENDOR) + "\n\n" +
						   "CL_PLATFORM_VERSION: " + GetPlatformInfo(CL_PLATFORM_VERSION) + "\n\n" +
						   "CL_PLATFORM_PROFILE: " + GetPlatformInfo(CL_PLATFORM_PROFILE) + "\n\n" +
						   "CL_PLATFORM_EXTENSIONS: " + GetPlatformInfo(CL_PLATFORM_EXTENSIONS) + "\n\n"  ;

		info += "CL_DEVICE_TYPE: " + GetDeviceInfo(CL_DEVICE_TYPE) + "\n\n" +
				"CL_DEVICE_NAME: " + GetDeviceInfo(CL_DEVICE_NAME) + "\n\n" +
				"CL_DEVICE_VENDOR: " + GetDeviceInfo(CL_DEVICE_VENDOR) + "\n\n" +
				"CL_DEVICE_VENDOR_ID: " + GetDeviceInfo(CL_DEVICE_VENDOR_ID) + "\n\n" +
				"CL_DEVICE_MAX_MEM_ALLOC_SIZE: " + GetDeviceInfo(CL_DEVICE_MAX_MEM_ALLOC_SIZE) + "\n\n" +
				"CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE: " + GetDeviceInfo(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE) + "\n\n" +
				"CL_DEVICE_GLOBAL_MEM_SIZE: " + GetDeviceInfo(CL_DEVICE_GLOBAL_MEM_SIZE) + "\n\n" +
				"CL_DEVICE_MAX_COMPUTE_UNITS: " + GetDeviceInfo(CL_DEVICE_MAX_COMPUTE_UNITS) + "\n\n" +
				"CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: " + GetDeviceInfo(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS) + "\n\n" +
				"CL_DEVICE_MAX_WORK_ITEM_SIZES: " + GetDeviceInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES) + "\n\n" +
				"CL_DEVICE_MAX_WORK_GROUP_SIZE: " + GetDeviceInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE) + "\n";

		return info;
	}
	catch (const std::exception &e)
	{
		throw std::exception(e.what());
	}
	
	return std::string();
}

std::vector<cl_platform_id> rdps::Cl::Dispositive::GetPlatforms()
{
	cl_uint size = 0;
	cl_int status = clGetPlatformIDs(0, nullptr, &size);
	if (status != CL_SUCCESS)
		throw std::out_of_range("Unable to verify the platforms. ERROR: "
								+ std::to_string(status));

	cl_platform_id *p = new cl_platform_id[size];
	status = clGetPlatformIDs(size, p, nullptr);
	if (status != CL_SUCCESS)
		throw std::out_of_range("Unable to capture the platforms. ERROR: "
							     + std::to_string(status));

	return std::vector<cl_platform_id>(&p[0], &p[size]);
}

std::vector<cl_device_id> rdps::Cl::Dispositive::GetDevices(cl_platform_id _platform, 
															cl_device_type type)
{
	cl_uint size = 0;
	cl_int status = clGetDeviceIDs(_platform, type, 0, nullptr, &size);
	if (status != CL_SUCCESS)
		throw std::out_of_range("Unable to verify the devices. ERROR: "
							    + std::to_string(status));

	cl_device_id *d = new cl_device_id[size];
	status = clGetDeviceIDs(_platform, type, size, d, nullptr);
	if (status != CL_SUCCESS)
		throw std::out_of_range("Unable to capture the devices. ERROR: "
								+ std::to_string(status));

	return std::vector<cl_device_id>(&d[0], &d[size]);
}

std::vector<cl_device_id> rdps::Cl::Dispositive::GetDevices(cl_device_type type)
{
	return GetDevices(platform, type);
}

void rdps::Cl::Dispositive::SetPlatform(cl_platform_id _platform)
{
	if (!platform)
		platform = platform;
}

void rdps::Cl::Dispositive::SetDevice(cl_device_id device)
{
	if (!device)
		device = device;
}


 