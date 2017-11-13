#ifndef	__COMMAND_QUEUE_COMPONENTE_H__
#define	__COMMAND_QUEUE_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "MemObjectComponent.h"
#include "..\..\Util\LogError.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponent;
		class DeviceComponent;
		class ItensWorkGroupComponent;
		class KernelComponent;

		/********************************************************************************************************************************************
		 *
		 * Classe que contem a fila para enfileirar, escrever e ler os objetos 
		 * do kernel 
		 *
		 ********************************************************************************************************************************************/
		class CommmandQueueComponent : BaseClComponent<cl_command_queue>
		{
		private:
			/*----------------------------------------------------------------------------------------------------------------------------------------
			* Função auxiliar que cria o CommandQueue baseado no contexto e no dispositivo e o retorna.
			*-----------------------------------------------------------------------------------------------------------------------------------------*/
			cl_command_queue Create(const ContextComponent &context,
							  const DeviceComponent &device);

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a construção da Fila utilizando um  Contexto e um device já criado.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const ContextComponent &context, 
								    const DeviceComponent &device);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_command_queue já construido fora.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const cl_command_queue &queue);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de cópia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const CommmandQueueComponent &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a função Release();
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~CommmandQueueComponent();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destroi o Contexto.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função que retorna uma string contendo as informações da fila
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_command_queue_info paramName);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar para a leitura dos dados de retorna da função kernel.
			 * Recebe o Objeto de memória referente ao buffer na CPU/DISPOSITIVO,
			 * o tamanho do buffer e o a referencia do buffer.
			 * Generico por que pode ser retornado qualquer tipo de dados validos.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &ReadBuffer(const MemObjectComponent &memObj, const size_t size, void *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar para a Escrita dos dados da função kernel no DISPOSITIVO.
			 * Recebe o Objeto de memória referente ao buffer na CPU/DISPOSITIVO,
			 * o tamanho do buffer e o a referencia do buffer.
			 * Generico por que pode ser lido qualquer tipo de dados validos.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &WriteBuffer(const MemObjectComponent &memObj, const size_t size, void *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que dá o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a referência da kernel que será executado, Referência ao número de
			 * dimenções dos grupos de trabalho, números de itens globais e itens locais em cada grupo.
			 * os itens de trabalho são necessários para a execução com sucesso.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &EnqueueNDRangeKernel(const KernelComponent &kernel, const ItensWorkGroupComponent &itens);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que dá o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a referência da kernel que será executado.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &EnqueueTask(const KernelComponent &kernel);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Função de sobrecar de operador para cópia, chama a função de cópia do pai.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			inline CommmandQueueComponent &operator=(const CommmandQueueComponent &other)
			{
				if (this != &other)
					BaseClComponent<Type>::operator=(other);
				return (*this);
			}
		};

	CL_END
RDPS_END

#endif//__COMMAND_QUEUE_COMPONENTE_H__