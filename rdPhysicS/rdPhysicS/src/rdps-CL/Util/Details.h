#ifndef	__DETAILS_H__
#define	__DETAILS_H__

#include "../Application/ClConfig.h"

namespace rdps
{
	namespace Cl
	{
		class ProgramComponent;
		class DeviceComponent;
		class KernelComponent;
		/******************************************************************************
		 *
		 * Classe auxiliar para verificar as informações dos dispositivos
		 * (placas de video, processador, etc.)
		 *
		 ******************************************************************************/
		class Details
		{
		public:
			/*-------------------------------------------------------------------------
			 *Verifica os detalhes da plataforma 
			 *e retorna uma string com o resultado.
			 *Recebe a plataforma desejada e o parametro
			 *de verificação. Exemplo:
			 *DisplayPlatformInfo(platform, CL_PLATFORM_NAME);
			 *-------------------------------------------------------------------------*/
			static std::string DisplayPlatformInfo(cl_platform_id platform,
												   cl_platform_info paramName);

			/*-------------------------------------------------------------------------
			 *Verifica todos detalhes do device e retorna 
			 *uma string com apenas um dos resultados
			 *Recebe o device desejado e o parametro
			 *de verificação. Exemplo:
			 * std::string aux = DisplayDeviceDetails(device, CL_DEVICE_TYPE);
			 *-------------------------------------------------------------------------*/
			static std::string DisplayDeviceDetails(cl_device_id device,
													cl_device_info paramName);

			static std::string DisplayBuildInfo(const ProgramComponent &program, 
												const DeviceComponent &device, 
												const cl_program_build_info paramName);
			//clGetKernelWorkGroupInfo()
			static std::string DisplayKernelWorkGroupInfo(const KernelComponent &kernel,
														  const DeviceComponent &device, 
														  const cl_kernel_work_group_info paramName);
		};
	}
}

#endif//__DETAILS_H__