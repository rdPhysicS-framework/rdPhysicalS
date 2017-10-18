#ifndef	__DEVICE_COMPONENTE_H__
#define	__DEVICE_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class PlatformComponent;
		/*************************************************************************************************
		 *
		 * Classe que contem o id do device openCL selecionado.
		 * Referente dispositivo onde será executado o programa OpenCL
		 *
		 *************************************************************************************************/
		class DeviceComponent : public BaseClComponent<cl_device_id>
		{
		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------*/
			DeviceComponent();
			/*---------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_device_id já construido fora.
			 *---------------------------------------------------------------------------------------------*/
			DeviceComponent(const cl_device_id &device);
			/*---------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *----------------------------------------------------------------------------------------------*/
			DeviceComponent(const DeviceComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *--------------------------------------------------------------------------------------------*/
			~DeviceComponent();

			virtual void Release();
			virtual void Retain();

			/*--------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações do Device.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_device_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Função de sobrecar de operadorga para cópia, chama a função de cópia do pai.
			 *--------------------------------------------------------------------------------------------*/
			inline DeviceComponent &operator=(const DeviceComponent &other)
			{
				if (this != &other)
					object = other.object;
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__DEVICE_COMPONENTE_H__