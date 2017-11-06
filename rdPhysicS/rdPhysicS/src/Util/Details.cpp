#include "Details.h"
#include "..\rdps-CL\Application\ProgramComponent.h"
#include "..\rdps-CL\Application\DeviceComponent.h"
#include "..\rdps-CL\Application\KernelComponent.h"
#include "LogError.h"

USING_RDPS
USING_CL

std::string Details::DisplayPlatformInfo(cl_platform_id platform, 
												   cl_platform_info paramName)
{
	cl_int status = 0;
	size_t paramSize = 0;

	status = clGetPlatformInfo(platform, paramName, 0, nullptr, &paramSize);
	if (status != CL_SUCCESS)
		Logger::Log(PLATFORM_COMPONENT_INFO, status, "Unable to find any OpenCL platform information");

	char *moreInfo = new char[paramSize];
	status = clGetPlatformInfo(platform, paramName, paramSize, moreInfo, nullptr);
	if (status != CL_SUCCESS)
		Logger::Log(PLATFORM_COMPONENT_INFO, status, "Unable to find any OpenCL platform information");

	return std::string(moreInfo);
}

std::string Details::DisplayDeviceDetails(cl_device_id device,
												    cl_device_info paramName)
{
	cl_int status = 0;
	size_t paramSize = 0;

	status = clGetDeviceInfo(device, paramName, 0, nullptr, &paramSize);
	if (status != CL_SUCCESS)
		Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");

	std::string info;

	switch (paramName)
	{
		case CL_DEVICE_TYPE:
		{
			cl_device_type *type = new cl_device_type[paramSize];

			status = clGetDeviceInfo(device, paramName, paramSize, type, nullptr);
			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");

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
			status = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);

			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");

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

			status = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);
			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");
			status = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &maxWIDimensions, nullptr);
			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");

			info = "Maximum number of work-items in each dimension: (  ";
			for (cl_uint i = 0; i < maxWIDimensions; i++)
				info += std::to_string(ret[i]) + " ";

			info += ")";

			delete ret;
			return info;
		}
		break;

		case CL_DEVICE_MAX_WORK_GROUP_SIZE:
		{
			size_t *ret = new size_t[paramSize];
			status = clGetDeviceInfo(device, paramName, paramSize, ret, nullptr);

			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");


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
			status = clGetDeviceInfo(device, paramName, paramSize, data, nullptr);

			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");


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

			status = clGetDeviceInfo(device, paramName, paramSize, size, nullptr);

			if (status != CL_SUCCESS)
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain devices info for param\n");

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
			status = clGetDeviceInfo(device, paramName, paramSize, size, NULL);

			if (status != CL_SUCCESS) 
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain device name/vendor info for param\n");

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
			status = clGetDeviceInfo(device, paramName, paramSize, &size, NULL);

			if (status != CL_SUCCESS) 
				Logger::Log(DEVICE_COMPONENT_INFO, status, "Unable to obtain device name/vendor info for param\n");

			info = "Local memory: " + std::to_string(size) + " bits";

			return info;
		}
		break;
	}

	return std::string();
}

std::string Details::DisplayBuildInfo(const ProgramComponent &program, 
												const DeviceComponent &device, 
												const cl_program_build_info paramName)
{
	size_t size;
	int status = clGetProgramBuildInfo(program(), device(),
									   paramName, 0, nullptr, &size);
	if (status != CL_SUCCESS)
	{
		Logger::Log(PROGRAM_BUILD_INFO, status, 
					"Error when verifying the information"
					"of the build of the program. ");
	}

	char *log = new char[size];
	status = clGetProgramBuildInfo(program(), device(),
								   paramName, size, log, 0);
	if (status != CL_SUCCESS)
	{
		Logger::Log(PROGRAM_BUILD_INFO, status,
				    "Error when verifying the information"
				    "of the build of the program. ");
	}

	std::string info = log;
	delete log;
	return info;
}

std::string Details::DisplayKernelInfo(const KernelComponent & kernel, const cl_kernel_info paramName)
{
	size_t size;
	int status = clGetKernelInfo(kernel(), paramName, 0, nullptr, &size);
	if (status != CL_SUCCESS)
	{
		Logger::Log(KERNEL_COMPONENT_INFO, status,
					"Unable to obtain kernel info for param\n");
	}

	std::string info;
	switch (paramName)
	{
		case CL_KERNEL_FUNCTION_NAME:
		{
			char *ret = new char[size];

			status = clGetKernelInfo(kernel(), paramName, size, ret, nullptr);
			if (status != CL_SUCCESS)
			{
				Logger::Log(KERNEL_COMPONENT_INFO, status,
					"Unable to obtain kernel name/attributes info.\n");
			}
			info = ret;
			info += "\n";
			delete ret;
			break;
		}
		case CL_KERNEL_NUM_ARGS:
		case CL_KERNEL_REFERENCE_COUNT:
		{
			uint num;

			status = clGetKernelInfo(kernel(), paramName, size, &num, nullptr);
			if (status != CL_SUCCESS)
			{
				Logger::Log(KERNEL_COMPONENT_INFO, status,
					"Unable to obtain kernel NUM_ARGS/REFERENCE_COUNT info.\n");
			}
			switch (paramName)
			{
			case CL_KERNEL_NUM_ARGS:
				info = "Num argumnets: " + std::to_string(num) + ".\n";
				break;
			case CL_KERNEL_REFERENCE_COUNT:
				info = "Refence count: " + std::to_string(num) + ".\n";
				break;
			}
			break;
		}
	}
	
	return info;
}

size_t *Details::DisplayKernelWorkGroupInfo(const KernelComponent &kernel, 
										    const DeviceComponent &device, 
										    const cl_kernel_work_group_info paramName)
{
	size_t size;
	int status = clGetKernelWorkGroupInfo(kernel(), device(), paramName, 0, nullptr, &size);
	if (status != CL_SUCCESS)
	{
		Logger::Log(KERNEL_COMPONENT_INFO, status, 
				    "Unable to obtain kernel Work Group info.\n");
	}

	switch (paramName)
	{
		case CL_KERNEL_GLOBAL_WORK_SIZE:
		case CL_KERNEL_WORK_GROUP_SIZE:
		case CL_KERNEL_COMPILE_WORK_GROUP_SIZE:
		case CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE:
		{
			size_t *ret = new size_t[size];
			int status = clGetKernelWorkGroupInfo(kernel(), device(), paramName, size, ret, nullptr);
			if (status != CL_SUCCESS)
			{
				Logger::Log(KERNEL_COMPONENT_INFO, status,
					"Unable to obtain kernel Work Group info.\n");
			}
			return ret;
		}
		case CL_KERNEL_LOCAL_MEM_SIZE:
		case CL_KERNEL_PRIVATE_MEM_SIZE:
		{
			ulong *ret = new ulong[size];
			int status = clGetKernelWorkGroupInfo(kernel(), device(), paramName, size, ret, nullptr);
			if (status != CL_SUCCESS)
			{
				Logger::Log(KERNEL_COMPONENT_INFO, status,
					"Unable to obtain kernel Work Group info.\n");
			}
			return static_cast<size_t*>(ret);
		}
	}

	return nullptr;
}
