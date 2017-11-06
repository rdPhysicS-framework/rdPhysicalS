#ifndef	__BASE_CL_COMPONENTE_H__
#define	__BASE_CL_COMPONENTE_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN
		/*************************************************************************************************
		 *
		 * Classe base para todos os componente necessarios
		 * para a execu��o do programa openCL
		 *
		 *************************************************************************************************/
		template<class Type>
		class BaseClComponent
		{
		protected:
			typedef Type Type;
			Type object;

		public:
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * adiciona a referencia gen�ria para nulo
			 *---------------------------------------------------------------------------------------------*/
			BaseClComponent() : object(nullptr){}
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			BaseClComponent(const Type &_object) : object(_object){}
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 *--------------------------------------------------------------------------------------------*/
			virtual ~BaseClComponent(){}

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
			inline BaseClComponent<Type> &operator=
				(const BaseClComponent<Type> &other) 
			{
				if (object)
					Release();
				object = other.object;
				return (*this);
			}
			/*--------------------------------------------------------------------------------------------
			* Fun��o de sobrecar de operador para c�pia
			*--------------------------------------------------------------------------------------------*/
			inline BaseClComponent<Type> &operator=
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