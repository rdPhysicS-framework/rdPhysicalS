#include <iostream>
#include "src\rdps-CL\ClGlobalDef.h"
#include "src\rdps-CL\Util\UtilGlobalDef.h"
#include <SDL.h>

#include "src\GlobalDefs.h"

USING_RDPS
USING_CL

int main(int argc, char **argv)
{
	PlatformComponente p;
	DeviceComponente d;
	try
	{
		std::vector<PlatformComponente> platforms = PlatformComponente::GetPlatforms();
		p = platforms[0];
		std::string info = p.GetInfo(CL_PLATFORM_VERSION);

		std::cout << info << std::endl;

		std::vector<DeviceComponente> devices = p.GetDevices(CL_DEVICE_TYPE_ALL);
		d = devices[0];

		std::cout << "CL_PLATFORM_NAME: " << p.GetInfo(CL_PLATFORM_NAME) << std::endl << std::endl;
		std::cout << "CL_DEVICE_NAME: " << d.GetInfo(CL_DEVICE_NAME) << std::endl;
		std::cout << "CL_DEVICE_MAX_COMPUTE_UNITS: " << d.GetInfo(CL_DEVICE_MAX_COMPUTE_UNITS) << std::endl;
		std::cout << "CL_DEVICE_MAX_WORK_GROUP_SIZE: " << d.GetInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE) << std::endl << std::endl;

		ContextComponente c = ContextComponente(d);

		CommmandQueueComponente q = CommmandQueueComponente(c, d);

		ProgramComponente prog = ProgramComponente(c, LoaderFiles::LoadSource({ "src/resource/Test.cl" }));
		prog.BuildProgram(d, "");

		char out[20];
		KernelComponente k = KernelComponente(prog, "test");

		MemObjectComponente mem = MemObjectComponente(c, RETURN_DATA_READING, sizeof(out));

		k.SetArgument(0, mem());

		ItensWorkGroupComponente itens = ItensWorkGroupComponente({ 1 }, { 1 });
		q.EnqueueNDRangeKernel(k, itens);
		//q.EnqueueTask(k);
		q.ReadBuffer(mem, sizeof(out), out);

		std::cout << out << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}