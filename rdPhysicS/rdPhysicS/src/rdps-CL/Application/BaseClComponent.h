#ifndef	__BASE_CL_COMPONENTE_H__
#define	__BASE_CL_COMPONENTE_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN
		/*************************************************************************************************
		 *
		 * Classe base para todos os componente necessarios
		 * para a execução do programa openCL
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
			 * adiciona a referencia genéria para nulo
			 *---------------------------------------------------------------------------------------------*/
			BaseClComponent() : object(nullptr){}
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
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
			 * Função de sobrecar de operador para cópia
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
			* Função de sobrecar de operador para cópia
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