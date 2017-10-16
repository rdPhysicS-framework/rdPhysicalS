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

enum InfoComponenteCL
{
	PLATFORM_COMPOENETE,
	DEVICE_COMPONENTE,
	CONTEXT_COMPONENETE,
	COMMAND_QUEUE_COMPONENETE,
	PROGRAM_COMPONENETE,
	KERNEL_COMPONENETE,
	ALL_COMPONENTES
};

enum ActionFile
{
	RETURN_DATA_WRITING = (1 << 1),
	RETURN_DATA_READING = (1 << 2)
	//RETURN_DATA_COPY
};

typedef unsigned int uint;

#endif//__GLOBAL_DEFS_H__