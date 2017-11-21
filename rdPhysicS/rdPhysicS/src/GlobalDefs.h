#ifndef	__GLOBAL_DEFS_H__
#define	__GLOBAL_DEFS_H__

#define RDPS_BEGIN namespace rdps{
#define RDPS_END }
#define USING_RDPS using namespace rdps;
#define RDPS rdps::

#define CL_BEGIN namespace Cl{
#define CL_END }
#define USING_CL using namespace Cl;
#define CL Cl::

#define PKG_BEGIN namespace pkg{
#define PKG_END }
#define USING_PKG using namespace pkg;
#define PKG pkg::

#define FRWK_BEGIN namespace frwk{
#define FRWK_END }
#define USING_FRWK using namespace frwk;
#define FRWK frwk::

#define PDCT_BEGIN namespace pdct{
#define PDCT_END }
#define USING_PDCT using namespace pdct;
#define PDCT pdct::

//#define RT_BEGIN namespace rt{
//#define RT_END }
//#define RT rt::
//#define USING_RT using namespace rt;

#define CLPATH "resource/"
#define IMAGE_PATH "results/"

#define EMPTY_BUFFER 0xFFFFFF
#define FREE_LOCATION 0
#define BUSY_LOCATION -1

#define ARRAY_WITHOUT_INDEX -1

/*ERROR MESSAGE */
#define ERROR_MSG_EMPTY_ERROR_MESSAGE ""
#define ERROR_MSG_PLATFORM_INVALID_VALUE     "CL_INVALID_VALUE: any of the parameters may be wrong."
#define ERROR_MSG_INVALID_PLATFORM           "CL_INVALID_PLATFORM: invalid platform."
#define ERROR_MSG_INVALID_VALUE              "CL_INVALID_VALUE: num_entries can be zero or device_type is not NULL or"   \
								             " both num_devices and device_type are NULL or invalid parameters."
#define ERROR_MSG_CONTEXT_INVALID_VALUE      "CL_INVALID_VALUE: the invalid context property name; or devices is NULL"   \
											 "or num_devices is equal to zero; or if pfn_notify is NULL, or user_data"   \
											 " is not NULL."
#define ERROR_MSG_INVALID_DEVICE_TYPE        "CL_INVALID_DEVICE_TYPE: invalid device_type"
#define ERROR_MSG_DEVICE_NOT_FOUND           "CL_DEVICE_NOT_FOUND: no OpenCL device matches the type of device found."
#define ERROR_MSG_HOST_MEMORY                "CL_OUT_OF_HOST_MEMORY: failed to allocate the resources required by the"   \
										     " OpenCL implementation in the host."
#define ERROR_MSG_OUT_OF_RESOURCES           "CL_OUT_OF_RESOURCES: failed to allocate resources required by the OpenCL"   \
											 " implementation on the device."
#define ERROR_MSG_INVALID_PLATFORM_DEVICE    "CL_INVALID_PLATFORM: invalid patafroma or device is NULL or num_devices "   \
											 "is equal to zero."
#define ERROR_MSG_CONTEXT_INVALID_PROPERTY	 "CL_INVALID_PROPERTY: the invalid context property name."
#define ERROR_MSG_INVALID_DEVICE_PLATFORM	 "CL_INVALID_DEVICE: devices may contain an invalid device or is not "	      \
											 "associated with the specified platform."
#define ERROR_MSG_DEVICE_NOT_AVAILABLE	     "CL_DEVICE_NOT_AVAILABLE: device is currently not available."
#define ERROR_MSG_INVALID_CONTEXT			 "CL_INVALID_CONTEXT: context invalid or NULL."
#define ERROR_MSG_INVALID_DEVICE_CONTEXT	 "CL_INVALID_DEVICE: invalid device or device is not associated with context."
#define ERROR_MSG_QUEUE_INVALID_VALUE		 "CL_INVALID_VALUE: invalid specified values"
#define ERROR_MSG_INVALID_QUEUE_PROPERTIES   "CL_INVALID_QUEUE_PROPERTIES: specified values not supported by the device."
#define ERROR_MSG_INVALID_COMMAND_QUEUE      "CL_INVALID_COMMAND_QUEUE: invalid command_queue."
#define ERROR_MSG_INVALID_DEVICE			 "CL_INVALID_DEVICE: invalid device"
#define ERROR_MSG_INVALID_PROPERTY		     "CL_INVALID_PROPERTY: the invalid context property name."
#define ERROR_MSG_CONTEXT_INVALID_DEVICE     "CL_INVALID_DEVICE: devices may contain an invalid device or is not"		   \
										     " associated with the specified platform."
#define ERROR_MSG_PROGRAM_INVALID_VALUE		 "CL_INVALID_VALUE: (WithSource)Count is zero or entry strings is NULL or "    \
											 "(WithBinary)device list is NULL or num_devices is zero, or binaries is NULL" \
											 " or lengths is zero"
#define ERROR_MSG_INVALID_BYNARY			 "CL_INVALID_BYNARY: invalid program Binary."
#define ERROR_MSG_INVALID_PROGRAM			 "CL_INVALID_PROGRAM: invalid program."
#define ERROR_MSG_INVALID_PROGRAM_EXECUTABLE "CL_INVALID_PROGRAM_EXECUTABLE: program executable has not been built for at "\
											 "least one device in the list of devices associated with program"
#define ERROR_MSG_INVALID_DEVICE_PROGRAM     "CL_INVALID_DEVICE: device is not in the associated with program"
//#define TO_STRING(x) std::to_string(x)

//#define WORLD_GET World::Get()
#define WORLD_GET_APP World::GetApp()

#define BLACK RT::Vec3f(0.0f, 0.0f, 0.0f)
#define WHITE RT::Vec3f(1.0f, 1.0f, 1.0f)

enum ComponentCL
{
	PLATFORM_COMPONENT,
	DEVICE_COMPONENT,
	CONTEXT_COMPONENT,
	COMMAND_QUEUE_COMPONENT,
	PROGRAM_COMPONENT,
	KERNEL_COMPONENT,
	ALL_COMPONENTS
};

enum InfoComponentCL
{
	PLATFORM_COMPONENT_CREATE,
	DEVICE_COMPONENT_CREATE,
	CONTEXT_COMPONENT_CREATE,
	COMMAND_QUEUE_COMPONENT_CREATE,
	PROGRAM_COMPONENT_CREATE,
	KERNEL_COMPONENT_CREATE,

	PLATFORM_COMPONENT_INFO,
	DEVICE_COMPONENT_INFO,
	CONTEXT_COMPONENT_INFO,
	COMMAND_QUEUE_COMPONENT_INFO,
	PROGRAM_COMPONENT_INFO,
	PROGRAM_BUILD_INFO,
	KERNEL_COMPONENT_INFO,
};

enum ActionFile
{
	NONE,
	RETURN_DATA_WRITING = (1 << 1),
	RETURN_DATA_READING = (1 << 2)
	//RETURN_DATA_COPY
};

enum TypeBRDF
{
	AMBIENT,
	DIFFUSE,
	GLOSSY_SPECULAR,
	PERFECT_SPECULAR
};

enum TypeObject
{
	CUBE,
	MESH,
	PLANE,
	RECTANGLE,
	SPHERE
};

enum TypeMaterial
{
	EMISSIVE_MATERIAL,
	SIMPLE_MATERIAL,
	PHONG_MATERIAL,
	REFLECT_MATERIAL,
	TRANSPARENT_MATERIAL
};

enum TypeLight
{
	AMBIENT_LIGHT,
	AMBIENT_OCLUDER_LIGHT,
	AREA_LIGHT,
	POINT_LIGHT
};

enum CollaboratorsFunction
{
	PACKER_OF_OBJECTS,
	DELIVERER_OF_OBJECTS,
	MANAGER_OF_OBJECTS,
	GENERAL_MANAGER
};

typedef unsigned int uint;
typedef unsigned __int64 ulong;
#endif//__GLOBAL_DEFS_H__