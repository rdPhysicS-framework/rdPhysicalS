#ifndef	__COMMAND_QUEUE_COMPONENTE_H__
#define	__COMMAND_QUEUE_COMPONENTE_H__

#include "BaseClComponent.h"
#include "ClConfig.h"
#include "MemObjectComponente.h"
#include "../Util/LogError.h"

RDPS_BEGIN
	CL_BEGIN
		class ContextComponente;
		class DeviceComponente;
		class ItensWorkGroupComponente;
		class KernelComponente;

		/********************************************************************************************************************************************
		 *
		 * Classe que contem a fila para enfileirar, escrever e ler os objetos 
		 * do kernel 
		 *
		 ********************************************************************************************************************************************/
		class CommmandQueueComponente : BaseClComponente<cl_command_queue>
		{
		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai nullptr
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Ocorre a constru��o da Fila utilizando um  Contexto e um device j� criado.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente(const ContextComponente &context, 
								    const DeviceComponente &device);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Adiciona a referencia do pai um cl_command_queue j� construido fora.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente(const cl_command_queue &queue);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de c�pia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente(const CommmandQueueComponente &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor
			 * Destroi chamando a fun��o Release();
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~CommmandQueueComponente();
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
			template<class T>
			inline CommmandQueueComponente &ReadBuffer(const MemObjectComponente &memObj, const size_t size, T *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar para a Escrita dos dados da fun��o kernel no DISPOSITIVO.
			 * Recebe o Objeto de mem�ria referente ao buffer na CPU/DISPOSITIVO,
			 * o tamanho do buffer e o a referencia do buffer.
			 * Generico por que pode ser lido qualquer tipo de dados validos.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline CommmandQueueComponente &WriteBuffer(const MemObjectComponente &memObj, const size_t size, T *data);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que d� o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a refer�ncia da kernel que ser� executado, Refer�ncia ao n�mero de
			 * dimen��es dos grupos de trabalho, n�meros de itens globais e itens locais em cada grupo.
			 * os itens de trabalho s�o necess�rios para a execu��o com sucesso.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente &EnqueueNDRangeKernel(const KernelComponente &kernel, const ItensWorkGroupComponente &itens);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que d� o comando para ocorrer o processamento dos dados no DISPOSITIVO.
			 * Recebe como parametro a refer�ncia da kernel que ser� executado.
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			CommmandQueueComponente &EnqueueTask(const KernelComponente &kernel);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o de sobrecar de operador para c�pia, chama a fun��o de c�pia do pai.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			inline CommmandQueueComponente &operator=(const CommmandQueueComponente &other)
			{
				if (this != &other)
					BaseClComponente<Type>::operator=(other);
				return (*this);
			}
		};

		//posteriormente passa uma classe ArrayBuffer contendo o id do mem_obj, 
		//os dados do do buffer, tamanho do buffer em bytes e quantidade de elementos 
		//no buffer.
		template<class T>
		inline CommmandQueueComponente 
					&CommmandQueueComponente::ReadBuffer(const MemObjectComponente &memObj,
														const size_t size, T *data)
		{
			/*adicionar mem_obj para funcionar*/
			if (int status = clEnqueueReadBuffer(object, memObj(), CL_TRUE,
												 0, sizeof(T) * size, data, 
												 0, nullptr, nullptr       ))
			{
				Logger::Log("ERROR when writing the data in the buffer."
							"\nERROR: " + std::to_string(status));
			}
			return (*this);
		}

		template<class T>
		inline CommmandQueueComponente 
				&CommmandQueueComponente::WriteBuffer(const MemObjectComponente &memObj, 
													 const size_t size, T *data)
		{
			/*adicionar mem_obj para funcionar*/
			if (int status = clEnqueueWriteBuffer(object, memObj(), CL_TRUE, 
												  0, sizeof(T) * size, data, 
												  0, nullptr, nullptr))
			{
				/****Tratar erro****/
			}
			return (*this);
		}
	CL_END
RDPS_END

#endif//__COMMAND_QUEUE_COMPONENTE_H__