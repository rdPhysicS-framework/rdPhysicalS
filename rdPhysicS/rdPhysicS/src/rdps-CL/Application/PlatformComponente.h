#ifndef	__PLATFOR_COMPONENTE_H__
#define	__PLATFOR_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class DeviceComponente;

		/*************************************************************************************************
		 *
		 * Classe que contem o id da plataforma openCL selecionada,
		 * e lista os devices disponiveis.
		 *
		 *************************************************************************************************/
		class PlatformComponente : public BaseClComponente<cl_platform_id>
		{
		public:
			/*---------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia nullptr
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponente();
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia um cl_platform_id já contruido fora.
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponente(const cl_platform_id &_id);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponente(const PlatformComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor padrão vazio, não faz nada.
			 *--------------------------------------------------------------------------------------------*/
			~PlatformComponente();

			/*--------------------------------------------------------------------------------------------
			 * Função padrão, não faz nada.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release() {}
			/*--------------------------------------------------------------------------------------------
			 * Função padrão, não faz nada.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Retain() {}
			/*--------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações do Plataforma.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_platform_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Função que retorna um vector contendo tadas as plataformas.
			 * Função static, que poder ser chamada sem a necessidade de existir um objeto.
			 * Exemplo:
			 * std::vector<PlatformComponent> platforms = PlatformComponent::GetPlatforms();
			 *--------------------------------------------------------------------------------------------*/
			static std::vector<PlatformComponente> GetPlatforms();
			/*--------------------------------------------------------------------------------------------
			* Função que retorna um vector contendo tadas os dispositivos.
			* Cada plataforma retorna sua lista de dispositivos.
			* Exemplo:
			* std::vector<DeviceComponent> divices = platfor.GetPlatforms();
			*--------------------------------------------------------------------------------------------*/
			std::vector<DeviceComponente> GetDevices(const cl_device_type type);
			/*--------------------------------------------------------------------------------------------
			* Função de sobrecar de operador para cópia, chama a função de cópia do pai.
			*--------------------------------------------------------------------------------------------*/
			inline PlatformComponente &operator=(const PlatformComponente &other)
			{
				if (this != &other)
					object = other.object;
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__PLATFOR_COMPONENTE_H__