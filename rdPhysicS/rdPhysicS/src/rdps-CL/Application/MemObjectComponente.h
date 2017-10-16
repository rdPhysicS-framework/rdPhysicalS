#ifndef	__MEM_OBJECT_COMPONENTE_H__
#define	__MEM_OBJECT_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponente;
		/************************************************************************************************
		*
		* Classe que contem a referencia ao objeto de mem�ria
		* para leitura e escrita da HOST para DISPOSITIVO/ DISPOSITIVO para HOST
		*
		************************************************************************************************/
		class MemObjectComponente : public BaseClComponente<cl_mem>
		{
		public:
			/*-------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponente();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o do objeto de mem�ria utilizando um contexto
			 * j� existente, e o adiciona a referencia do pai.
			 * O parametro flags define para que ser� esse objeto (ESCRITA ou LEITURA),
			 * size � o tamanho do buffer de dados.
			 * cl_mem faz a o meio campo entre a referencia dos dados na CPU com a DISPOSITIVO.
			 *------------------------------------------------------------------------------------------*/
			MemObjectComponente(const ContextComponente &context,
							    const  ActionFile typeAction,
							    const size_t size);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_mem j� contruido fora.
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponente(const cl_mem &memObj);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponente(const MemObjectComponente &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *--------------------------------------------------------------------------------------------*/
			~MemObjectComponente();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o objeto de mem�ria.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			
			/*--------------------------------------------------------------------------------------------
			 * Fun��o auxiliar do tipo cl_mem que cria  um objeto de mem�ria e o retorna. 
			 * Fun��o static n�o necessita de um instancia para ser chamada.
			 * Toda vez que um for alterado algum dado do buffer que o objeto de mem�ria
			 * est� referenciado, deve-se criar outro destruido o anterior com Release(), 
			 * e utilizando a fun��o de c�pia operator=.
			 * Exemplo:
			 * memObj = MemObjectComponent::Create(context, CL_MEM_WRITE_ONLY, size);
			 * --memObj j� existe--
			 *--------------------------------------------------------------------------------------------*/
			static cl_mem Create(const ContextComponente &context,
								 const  ActionFile typeAction,
							     const size_t size);
			
			/*--------------------------------------------------------------------------------------------
			 * Fun��o de sobrecarga de operador para c�pia, chama a fun��o de c�pia do pai.
			 *--------------------------------------------------------------------------------------------*/
			inline MemObjectComponente &operator=(const MemObjectComponente &other)
			{
				if (this != &other)
					BaseClComponente<Type>::operator=(other);
				return (*this);
			}
		};
	CL_END
RDPS_END

#endif//__MEM_OBJECT_COMPONENTE_H__