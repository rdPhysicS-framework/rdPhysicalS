#ifndef	__GLOBAL_DEFS_H__
#define	__GLOBAL_DEFS_H__

#define RDPS_BEGIN namespace rdps{
#define RDPS_END }
#define RDPS rdps::
#define USING_RDPS using namespace rdps;

#define CL_BEGIN namespace Cl{
#define CL_END }
#define CL Cl::
#define USING_CL using namespace Cl;

#define PKG_BEGIN namespace pkg{
#define PKG_END }
#define PKG pkg::
#define USING_PKG using namespace pkg;

#define CLPATH "src/resource/"
#define IMAGE_PATH "results/"

#define EMPTY_BUFFER 1
#define FREE_LOCATION 0
#define BUSY_LOCATION -1

/*ERROR MESSAGE */
#define EMPTY_ERROR_MESSAGE ""
#define PLATFORM_INVALID_VALUE "CL_INVALID_VALUE: any of the parameters may be wrong."
#define INVALID_PLATFORM "CL_INVALID_PLATFORM: invalid platform."
#define INVALID_VALUE "CL_INVALID_VALUE: num_entries can be zero or device_type is not NULL or both num_devices and device_type are NULL."
#define CONTEXT_INVALID_VALUE "CL_INVALID_VALUE: the invalid context property name; or devices is NULL"\
					  "or num_devices is equal to zero; or if pfn_notify is NULL, or user_data is not NULL.";
#define INVALID_DEVICE_TYPE "CL_INVALID_DEVICE_TYPE: invalid device_type"
#define DEVICE_NOT_FOUND "CL_DEVICE_NOT_FOUND: no OpenCL device matches the type of device found."
#define HOST_MEMORY "CL_OUT_OF_HOST_MEMORY: failed to allocate the resources required by the OpenCL implementation in the host."
#define OUT_OF_RESOURCES "CL_OUT_OF_RESOURCES: failed to allocate resources required by the OpenCL implementation on the device."
#define INVALID_PLATFORM_DEVICE "CL_INVALID_PLATFORM: invalid patafroma or device is NULL or num_devices is equal to zero."
#define CONTEXT_INVALID_PROPERTY "CL_INVALID_PROPERTY: the invalid context property name."
#define CL_INVALID_DEVICE_PLATFORM "CL_INVALID_DEVICE: devices may contain an invalid device or is not associated with the specified platform."
#define DEVICE_NOT_AVAILABLE "CL_DEVICE_NOT_AVAILABLE: device is currently not available."
#define INVALID_CONTEXT "CL_INVALID_CONTEXT: context invalid or NULL."
#define INVALID_DEVICE_CONTEXT "CL_INVALID_DEVICE: invalid device or device is not associated with context."
#define QUEUE_INVALID_VALUE "CL_INVALID_VALUE: invalid specified values"
#define INVALID_QUEUE_PROPERTIES "CL_INVALID_QUEUE_PROPERTIES: specified values not supported by the device."
#define INVALID_COMMAND_QUEUE "CL_INVALID_COMMAND_QUEUE: invalid command_queue."
#define INVALID_DEVICE "CL_INVALID_DEVICE: invalid device"
//#define TO_STRING(x) std::to_string(x)

enum InfoComponentCL
{
	PLATFORM_COMPONENT,
	DEVICE_COMPONENT,
	CONTEXT_COMPONENT,
	COMMAND_QUEUE_COMPONENT,
	PROGRAM_COMPONENT,
	KERNEL_COMPONENT,
	ALL_COMPONENTS,

	PLATFORM_COMPONENT_INFO,
	DEVICE_COMPONENT_INFO,
	CONTEXT_COMPONENT_INFO,
	COMMAND_QUEUE_COMPONENT_INFO,
	PROGRAM_COMPONENT_INFO,
	KERNEL_COMPONENT_INFO,
};

enum ActionFile
{
	RETURN_DATA_WRITING = (1 << 1),
	RETURN_DATA_READING = (1 << 2)
	//RETURN_DATA_COPY
};

typedef unsigned int uint;

#endif//__GLOBAL_DEFS_H__