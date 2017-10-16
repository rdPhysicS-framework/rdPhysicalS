#ifndef	__DISPOSITIVE_H__
#define	__DISPOSITIVE_H__

#include "ClConfig.h"

namespace rdps
{
	namespace Cl
	{
		/************************************************************************************************
		 *
		 * Classe conteiner para a plataforma e o dispositivo openCL,
		 * onde será executado o programa openCL.
		 *
		 ************************************************************************************************/
		class Dispositive
		{
		private:
			cl_platform_id platform;
			cl_device_id device;
			
		private:

		public:
			Dispositive(cl_platform_id platform = nullptr,
						cl_device_id device = nullptr     );
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna os detalhes da plataforma de acordo 
			 * com o nome da informação, retorna uma string. Exemplo:
			 * std::string aux = GetPlatformInfo(CL_PLATFORM_EXTENSIONS);
			 *-------------------------------------------------------------------------------------------*/
			std::string GetPlatformInfo(cl_platform_info name);
			
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna os detalhes do dispositivo de acordo
			 * com o nome da informação, retorna uma string. Exemplo:
			 * std::string aux = GetDeviceInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE);
			 *-------------------------------------------------------------------------------------------*/
			std::string GetDeviceInfo(cl_device_info name);
			
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna os detalhes completos tanto da plataforma
			 * como do device, retorna uma string. Exemplo:
			 * std::string aux = GetInfo();
			 *-------------------------------------------------------------------------------------------*/
			std::string GetInfo();
			
			/*-------------------------------------------------------------------------------------------
			 * Função que verifica e retorna uma lista(std::vector) contendo
			 * todas as plataformas em seu computador. Exemplo:
			 * std::vector<cl_platform_id> platforms = GetPlatforms();
			 *-------------------------------------------------------------------------------------------*/
			static std::vector<cl_platform_id> GetPlatforms();
			
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna uma lista de dispositivos, atrves de
			 * uma plataforma openCL celecionada. Exemplo:
			 * std::vector<cl_device_id> devices = GetDevices(platform, CL_DEVICE_TYPE_GPU);
			 * neste exeplo só será listadas os devices de GPU. Tara todos os dispositivos deve-se
			 * passa CL_DEVICE_TYPE_ALL.
			 *-------------------------------------------------------------------------------------------*/
			static std::vector<cl_device_id> GetDevices(cl_platform_id _platform, 
														cl_device_type type);
			
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna uma lista de dispositivos, atraves de
			 * uma plataforma openCL interna da classe conteiner(Dispositive).
			 * Recebendo como parametro apenas um tipo de dispositivo. Exemplo:
			 * std::vector<cl_device_id> devices = GetDevices(CL_DEVICE_TYPE_GPU);
			 * neste exeplo só será listadas os devices de GPU. Tara todos os dispositivos deve-se
			 * passa CL_DEVICE_TYPE_ALL.
			*-------------------------------------------------------------------------------------------*/
			std::vector<cl_device_id> GetDevices(cl_device_type type);
			
			/*-------------------------------------------------------------------------------------------
			 * Função que retorna um dos parametros contidos no container
			 * cl_platform_id platform, cl_device_id device. Passando
			 * um identificador de acesso, não listado na openCL Exemplo:
			 * cl_device_id aux = dispositive(CL_DEVICE_ID);
			 *-------------------------------------------------------------------------------------------*/
			template<class T>
			inline T operator[](int paramName)
			{
				return (paramName == PLATFORM_ID) ? platform :
					(paramName == DEVICE_ID) ? device :
					throw std::exception(
						"Invalid parameter name.\n");
			}
			
			inline cl_platform_id GetPlatform() const { return platform; }
			inline cl_device_id GetDevice() const { return device; }

			/*-------------------------------------------------------------------------------------------
			 *
			 *-------------------------------------------------------------------------------------------*/
			void SetPlatform(cl_platform_id _platform);
			
			/*-------------------------------------------------------------------------------------------
			*
			*-------------------------------------------------------------------------------------------*/
			void SetDevice(cl_device_id device);
		};

		/*template<typename T>
		inline T Dispositive::operator()(int paramName)
		{
			return (paramName == PLATFORM_ID) ? platform : 
				   (paramName == DEVICE_ID  ) ? device :
				    throw std::exception(
						"Invalid parameter name.\n");
		}*/
	}
}

#endif//__DISPOSITIVE_H__