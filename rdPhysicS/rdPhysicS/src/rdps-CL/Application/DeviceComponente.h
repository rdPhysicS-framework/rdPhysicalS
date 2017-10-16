#ifndef	__DEVICE_COMPONENTE_H__
#define	__DEVICE_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class PlatformComponente;
		/*************************************************************************************************
		 *
		 * Classe que contem o id do device openCL selecionado.
		 * Referente dispositivo onde ser� executado o programa OpenCL
		 *
		 *************************************************************************************************/
		class DeviceComponente : public BaseClComponente<cl_device_id>
		{
		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------*/
			DeviceComponente();
			/*---------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_device_id j� construido fora.
			 *---------------------------------------------------------------------------------------------*/
			DeviceComponente(const cl_device_id &device);
			/*---------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *----------------------------------------------------------------------------------------------*/
			DeviceComponente(const DeviceComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *--------------------------------------------------------------------------------------------*/
			~DeviceComponente();

			virtual void Release();
			virtual void Retain();

			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es do Device.
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_device_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operadorga para c�pia, chama a fun��o de c�pia do pai.
			 *--------------------------------------------------------------------------------------------*/
			inline DeviceComponente &operator=(const DeviceComponente &other)
			{
				if (this != &other)
					object = other.object;
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__DEVICE_COMPONENTE_H__