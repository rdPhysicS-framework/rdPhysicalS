#include "Details.h"
#include "..\Application\ProgramComponente.h"
#include "..\Application\DeviceComponente.h"
#include "..\Util\LogError.h"

std::string rdps::Cl::Details::DisplayPlatformInfo(cl_platform_id platform, 
												   cl_platform_info paramName)
{
	cl_int error = 0;
	size_t paramSize = 0;

	error = clGetPlatformInfo(platform, paramName, 0, nullptr, &paramSize);
	if (error != CL_SUCCESS)
		Logger::Log("Unable to find any OpenCL platform information");

	char *moreInfo = new char[paramSize];
	error = clGetPlatformInfo(platform, paramName, paramSize, moreInfo, nullptr);
	if (error != CL_SUCCESS)
		Logger::Log("Unable to find any OpenCL platform information");

	return std::string(moreInfo);
}

std::string rdps::Cl::Details::DisplayDeviceDetails(cl_device_id device,
												    cl_device_info paramName)
{
	cl_int error = 0;
	size_t paramSize = 0;

	error = clGetDeviceInfo(device, paramName, 0, nullptr, &paramSize);
	if (error != CL_SUCCESS)
		Logger::Log("Unable to obtain devices info for param\n");

	std::string info;

	switch (paramName)
	{
		case CL_DEVICE_TYPE:
		{
			cl_device_type *type = new cl_device_type[paramSize];

			error = clGetDeviceInfo(device, paramName, paramSize, type, nullptr);
			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");

			switch (*type)
			{
			case CL_DEVICE_TYPE_CPU:
				info = "CPU detected";
				break;
			case CL_DEVICE_TYPE_GPU:
				info = "GPU detected";
				break;
			case CL_DEVICE_TYPE_DEFAULT:
				info = "DEFAULT detected";
				break;
			}

			delete type;
			return info;
		}
		break;

		case CL_DEVICE_VENDOR_ID:
		case CL_DEVICE_MAX_COMPUTE_UNITS:
		case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
		{
			cl_uint *ret = new cl_uint[paramSize];
			error = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);

			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");

			switch (paramName)
			{
			case CL_DEVICE_VENDOR_ID:
				info = "Vedor ID: " + std::to_string(*ret);
				break;
			case CL_DEVICE_MAX_COMPUTE_UNITS:
				info = "Maximum number of parallel compute units: " + 
						std::to_string(*ret);
				break;
			case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
				info = "Maximum dimensions for global / local work - item IDs: " +
						std::to_string(*ret);
				break;
			}

			delete ret;
			return info;
		}
		break;

		case CL_DEVICE_MAX_WORK_ITEM_SIZES:
		{
			cl_uint maxWIDimensions;
			size_t *ret = new size_t[paramSize];

			error = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);
			error |= clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &maxWIDimensions, nullptr);
			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");

			info = "Maximum number of work-items in each dimension: (  ";
			for (int i = 0; i < maxWIDimensions; i++)
				info += std::to_string(ret[i]) + " ";

			info += ")";

			delete ret;
			return info;
		}
		break;

		case CL_DEVICE_MAX_WORK_GROUP_SIZE:
		{
			size_t *ret = new size_t[paramSize];
			error = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);

			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");


			info = "Maximum number of work-items in a work-group: " +
					std::to_string(*ret);

			delete ret;
			return info;
		}
		break;

		case CL_DEVICE_NAME:
		case CL_DEVICE_VENDOR:
		{
			char data[48];
			error = clGetDeviceInfo(device, paramName, paramSize, data, nullptr);

			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");


			switch (paramName)
			{
			case CL_DEVICE_NAME:
				info = "Device name is ";
				info += data;
				break;
			case CL_DEVICE_VENDOR:
				info = "Device vendor is ";
				info += data;
				break;
			}

			//delete data;
			return info;
		}
		break;


		case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
		{
			cl_uint *size = new cl_uint[paramSize];

			error = clGetDeviceInfo(device, paramName, paramSize, size, nullptr);

			if (error != CL_SUCCESS)
				Logger::Log("Unable to obtain devices info for param\n");

			info = "Device global cacheline size: " + 
					std::to_string(*size) + " bytes";

			delete size;
			return info;
		}
		break;
		case CL_DEVICE_GLOBAL_MEM_SIZE:
		case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
		{
			cl_ulong *size = new cl_ulong[paramSize];
			error = clGetDeviceInfo(device, paramName, paramSize, size, NULL);

			if (error != CL_SUCCESS) 
				Logger::Log("Unable to obtain device name/vendor info for param\n");

			switch (paramName) {
			case CL_DEVICE_GLOBAL_MEM_SIZE:
				info = "Device global mem: "          +
						std::to_string((*size) >> 20) +
						" mega-bytes"; 
				break;
			case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
				info = "Device max memory allocation: " +
						std::to_string((*size) >> 20)   + 
						" mega-bytes";
				break;
			}

			delete size;
			return info;
		}
		break;

		case CL_DEVICE_LOCAL_MEM_SIZE:
		{
			cl_ulong size = 0;
			error = clGetDeviceInfo(device, paramName, paramSize, &size, NULL);

			if (error != CL_SUCCESS) 
				Logger::Log("Unable to obtain device name/vendor info for param\n");

			info = "Local memory: " + std::to_string(size) + " bits";

			return info;
		}
		break;
	}

	return std::string();
}

std::string rdps::Cl::Details::DisplayBuildInfo(const ProgramComponente &program, 
												const DeviceComponente &device, 
												const cl_program_build_info paramName)
{
	size_t size;
	int status = clGetProgramBuildInfo(program(), device(),
									   paramName, 0, nullptr, &size);
	if (status != CL_SUCCESS)
	{
		Logger::Log("Error when verifying the information"
					  "of the build of the program. \nERROR" 
					  + std::to_string(status));
	}

	char *log = new char[size];
	status = clGetProgramBuildInfo(program(), device(),
								   paramName, size, log, 0);
	if (status != CL_SUCCESS)
	{
		Logger::Log("Error when verifying the information"
					  "of the build of the program. \nERROR"
					  + std::to_string(status));
	}

	std::string info = log;
	delete log;
	return info;
}
