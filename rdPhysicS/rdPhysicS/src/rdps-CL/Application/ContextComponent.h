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
			 * Função auxiliar que cria o contexto baseado no dispositivo e o retorna.
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
			 * Ocorre a construção do Contexto OpenCL utilizando um  Device já criado.
			 *------------------------------------------------------------------------------------------*/
			ContextComponent(const DeviceComponent &device, const cl_context_properties *prop = nullptr);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_context já construido fora.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent(const cl_context &context);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent(const ContextComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *--------------------------------------------------------------------------------------------*/
			~ContextComponent();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o Contexto.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			/*--------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações do contexto
			 *--------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_context_info paramName);
			/*--------------------------------------------------------------------------------------------
			 * Função de sobrecar de operador para cópia, chama a função de cópia do pai.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponent &operator=(const ContextComponent &other);
		};
	CL_END
RDPS_END

#endif//__CONTEXT_COMPONENTE_H__