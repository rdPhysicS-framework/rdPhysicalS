#ifndef	__CL_GLOBAL_DEF_H__
#define	__CL_GLOBAL_DEF_H__

#include "Application\PlatformComponente.h"
#include "Application\DeviceComponente.h"
#include "Application\ContextComponente.h"
#include "Application\CommandQueueComponente.h"
#include "Application\ProgramComponente.h"
#include "Application\KernelComponente.h"
#include "Application\MemObjectComponente.h"
#include "Application\ItensWorkGroupComponente.h"
#include "Util\Details.h"

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

#endif//__CL_GLOBAL_DEF_H__