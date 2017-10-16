#ifndef	__BASE_CL_COMPONENTE_H__
#define	__BASE_CL_COMPONENTE_H__

#include "../../GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN
		/*************************************************************************************************
		 *
		 * Classe base para todos os componente necessarios
		 * para a execu��o do programa openCL
		 *
		 *************************************************************************************************/
		template<class Type>
		class BaseClComponente
		{
		protected:
			typedef Type Type;
			Type object;

		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * adiciona a referencia gen�ria para nulo
			 *---------------------------------------------------------------------------------------------*/
			BaseClComponente() : object(nullptr){}
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			BaseClComponente(const Type &_object) : object(_object){}
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 *--------------------------------------------------------------------------------------------*/
			virtual ~BaseClComponente(){}

			virtual void Release() = 0;
			virtual void Retain() = 0;

			/*--------------------------------------------------------------------------------------------
			 * Retorna o object
			 *--------------------------------------------------------------------------------------------*/
			inline Type operator()() const { return object; }
			/*--------------------------------------------------------------------------------------------
			 * Retorna o object
			 *--------------------------------------------------------------------------------------------*/ 
			inline Type &operator()() { return object; }
			/*--------------------------------------------------------------------------------------------
			 * Retorna o object
			 *--------------------------------------------------------------------------------------------*/
			inline Type GetObject() const { return object; }
			/*--------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operador para c�pia
			 *--------------------------------------------------------------------------------------------*/
			inline BaseClComponente<Type> &operator=
				(const BaseClComponente<Type> &other) 
			{
				if (object)
					Release();
				object = other.object;
				return (*this);
			}
			/*--------------------------------------------------------------------------------------------
			* Fun��o de sobrecar de operador para c�pia
			*--------------------------------------------------------------------------------------------*/
			inline BaseClComponente<Type> &operator=
				(const Type &other)
			{
				if (object)
					Release();
				object = other;
				return (*this);
			}
		};
	CL_END
RDPS_END


#endif//__BASE_CL_COMPONENTE_H__