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
			* Fun��o auxiliar que cria o CommandQueue baseado no contexto e no dispositivo e o retorna.
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
			 * Ocorre a constru��o da Fila utilizando um  Contexto e um device j� criado.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const ContextComponent &context, 
								    const DeviceComponent &device);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_command_queue j� construido fora.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const cl_command_queue &queue);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent(const CommmandQueueComponent &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~CommmandQueueComponent();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destroi o Contexto.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Release();
			virtual void Retain();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que retorna uma string contendo as informa��es da fila
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			std::string GetInfo(const cl_command_queue_info paramName);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar para a leitura dos dados de retorna da fun��o kernel.
			 * Recebe o Objeto de mem�ria referente ao buffer na CPU/DISPOSITIVO,
			 * o tamanho do buffer e o a referencia do buffer.
			 * Generico por que pode ser retornado qualquer tipo de dados validos.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &ReadBuffer(const MemObjectComponent &memObj, const size_t size, void *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar para a Escrita dos dados da fun��o kernel no DISPOSITIVO.
			 * Recebe o Objeto de mem�ria referente ao buffer na CPU/DISPOSITIVO,
			 * o tamanho do buffer e o a referencia do buffer.
			 * Generico por que pode ser lido qualquer tipo de dados validos.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &WriteBuffer(const MemObjectComponent &memObj, const size_t size, void *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que d� o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a refer�ncia da kernel que ser� executado, Refer�ncia ao n�mero de
			 * dimen��es dos grupos de trabalho, n�meros de itens globais e itens locais em cada grupo.
			 * os itens de trabalho s�o necess�rios para a execu��o com sucesso.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &EnqueueNDRangeKernel(const KernelComponent &kernel, const ItensWorkGroupComponent &itens);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que d� o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a refer�ncia da kernel que ser� executado.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponent &EnqueueTask(const KernelComponent &kernel);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
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