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
			 * Adiciona no a referencia um cl_platform_id j� contruido fora.
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponente(const cl_platform_id &_id);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponente(const PlatformComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor padr�o vazio, n�o faz nada.
			 *--------------------------------------------------------------------------------------------*/
			~PlatformComponente();

			/*--------------------------------------------------------------------------------------------
			 * Fun��o padr�o, n�o faz nada.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release() {}
			/*--------------------------------------------------------------------------------------------
			 * Fun��o padr�o, n�o faz nada.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Retain() {}
			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es do Plataforma.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_platform_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna um vector contendo tadas as plataformas.
			 * Fun��o static, que poder ser chamada sem a necessidade de existir um objeto.
			 * Exemplo:
			 * std::vector<PlatformComponent> platforms = PlatformComponent::GetPlatforms();
			 *--------------------------------------------------------------------------------------------*/
			static std::vector<PlatformComponente> GetPlatforms();
			/*--------------------------------------------------------------------------------------------
			* Fun��o que retorna um vector contendo tadas os dispositivos.
			* Cada plataforma retorna sua lista de dispositivos.
			* Exemplo:
			* std::vector<DeviceComponent> divices = platfor.GetPlatforms();
			*--------------------------------------------------------------------------------------------*/
			std::vector<DeviceComponente> GetDevices(const cl_device_type type);
			/*--------------------------------------------------------------------------------------------
			* Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
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