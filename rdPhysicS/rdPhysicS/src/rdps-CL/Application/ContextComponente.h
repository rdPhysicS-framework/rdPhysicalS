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
			 * Ocorre a constru��o do Contexto OpenCL utilizando um  Device j� criado.
			 *------------------------------------------------------------------------------------------*/
			ContextComponente(const DeviceComponente &device, const cl_context_properties *prop = nullptr);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_context j� construido fora.
			 *--------------------------------------------------------------------------------------------*/
			ContextComponente(const cl_context &context);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			ContextComponente(const ContextComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *--------------------------------------------------------------------------------------------*/
			~ContextComponente();
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