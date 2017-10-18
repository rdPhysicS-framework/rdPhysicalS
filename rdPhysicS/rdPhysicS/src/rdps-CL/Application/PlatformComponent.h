#ifndef	__PLATFOR_COMPONENTE_H__
#define	__PLATFOR_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class DeviceComponent;

		/*************************************************************************************************
		 *
		 * Classe que contem o id da plataforma openCL selecionada,
		 * e lista os devices disponiveis.
		 *
		 *************************************************************************************************/
		class PlatformComponent : public BaseClComponent<cl_platform_id>
		{
		public:
			/*---------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia nullptr
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponent();
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona no a referencia um cl_platform_id j� contruido fora.
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponent(const cl_platform_id &_id);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			PlatformComponent(const PlatformComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor padr�o vazio, n�o faz nada.
			 *--------------------------------------------------------------------------------------------*/
			~PlatformComponent();

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
			static std::vector<PlatformComponent> GetPlatforms();
			/*--------------------------------------------------------------------------------------------
			* Fun��o que retorna um vector contendo tadas os dispositivos.
			* Cada plataforma retorna sua lista de dispositivos.
			* Exemplo:
			* std::vector<DeviceComponent> divices = platfor.GetPlatforms();
			*--------------------------------------------------------------------------------------------*/
			std::vector<DeviceComponent> GetDevices(const cl_device_type type);
			/*--------------------------------------------------------------------------------------------
			* Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
			*--------------------------------------------------------------------------------------------*/
			inline PlatformComponent &operator=(const PlatformComponent &other)
			{
				if (this != &other)
					object = other.object;
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__PLATFOR_COMPONENTE_H__