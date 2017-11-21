#ifndef	__CONTEXT_COMPONENTE_H__
#define	__CONTEXT_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class DeviceComponent;

		/************************************************************************************************
		 *
		 * Classe que contem o componenet de contexto openCl
		 *
		 ************************************************************************************************/
		class ContextComponent : public BaseClComponent<cl_context>
		{
		private:
			/*--------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que cria o contexto baseado no dispositivo e o retorna.
			 *--------------------------------------------------------------------------------------------*/
			cl_context Create(const DeviceComponent &device, const cl_context_properties *prop = nullptr);

		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------*/
			ContextComponent();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o do Contexto OpenCL utilizando um  Device j� criado.
			 *------------------------------------------------------------------------------------------*/
			ContextComponent(const DeviceComponent &device, const cl_context_properties *prop = nullptr);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_context j� construido fora.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent(const cl_context &context);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent(const ContextComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *--------------------------------------------------------------------------------------------*/
			~ContextComponent();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o Contexto.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			/*--------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es do contexto
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_context_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent &operator=(const ContextComponent &other);
		};
	CL_END
RDPS_END

#endif//__CONTEXT_COMPONENTE_H__