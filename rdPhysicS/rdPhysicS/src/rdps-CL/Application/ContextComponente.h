#ifndef	__CONTEXT_COMPONENTE_H__
#define	__CONTEXT_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class DeviceComponente;

		/************************************************************************************************
		 *
		 * Classe que contem o componenet de contexto openCl
		 *
		 ************************************************************************************************/
		class ContextComponente : public BaseClComponente<cl_context>
		{
		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------*/
			ContextComponente();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a construção do Contexto OpenCL utilizando um  Device já criado.
			 *------------------------------------------------------------------------------------------*/
			ContextComponente(const DeviceComponente &device, const cl_context_properties *prop = nullptr);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_context já construido fora.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponente(const cl_context &context);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *--------------------------------------------------------------------------------------------*/
			ContextComponente(const ContextComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *--------------------------------------------------------------------------------------------*/
			~ContextComponente();
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
			inline ContextComponente &operator=(const ContextComponente &other)
			{
				if (this != &other)
					BaseClComponente<Type>::operator=(other);
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__CONTEXT_COMPONENTE_H__