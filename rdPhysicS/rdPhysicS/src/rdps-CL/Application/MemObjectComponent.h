#ifndef	__MEM_OBJECT_COMPONENTE_H__
#define	__MEM_OBJECT_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponent;
		/************************************************************************************************
		*
		* Classe que contem a referencia ao objeto de memória
		* para leitura e escrita da HOST para DISPOSITIVO/ DISPOSITIVO para HOST
		*
		************************************************************************************************/
		class MemObjectComponent : public BaseClComponent<cl_mem>
		{
		
		public:
			/*-------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponent();
			/*------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a construção do objeto de memória utilizando um contexto
			 * já existente, e o adiciona a referencia do pai.
			 * O parametro flags define para que será esse objeto (ESCRITA ou LEITURA),
			 * size é o tamanho do buffer de dados.
			 * cl_mem faz a o meio campo entre a referencia dos dados na CPU com a DISPOSITIVO.
			 *------------------------------------------------------------------------------------------*/
			MemObjectComponent(const ContextComponent &context,
							    const  ActionFile typeAction,
							    const size_t size);
			/*--------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_mem já contruido fora.
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponent(const cl_mem &memObj);
			/*--------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponent(const MemObjectComponent &other);
			/*--------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *--------------------------------------------------------------------------------------------*/
			~MemObjectComponent();
			/*--------------------------------------------------------------------------------------------
			 * Destroi o objeto de memória.
			 *--------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			
			/*--------------------------------------------------------------------------------------------
			 * Função auxiliar do tipo cl_mem que cria  um objeto de memória e o retorna. 
			 * Função static não necessita de um instancia para ser chamada.
			 * Toda vez que for alterado algum dado do buffer que o objeto de meméria
			 * está referenciado, deve-se criar outro destruido o anterior com Release(), 
			 * e utilizando a função de cópia operator=.
			 * Exemplo:
			 * memObj = MemObjectComponent::Create(context, CL_MEM_WRITE_ONLY, size);
			 * --memObj já existe--
			 *--------------------------------------------------------------------------------------------*/
			static cl_mem Create(const ContextComponent &context,
								 const  ActionFile typeAction,
							     const size_t size);
			
			/*--------------------------------------------------------------------------------------------
			 * Função de sobrecarga de operador para cópia, chama a função de cópia do pai.
			 *--------------------------------------------------------------------------------------------*/
			MemObjectComponent &operator=(const MemObjectComponent &other);
		};
	CL_END
RDPS_END

#endif//__MEM_OBJECT_COMPONENTE_H__