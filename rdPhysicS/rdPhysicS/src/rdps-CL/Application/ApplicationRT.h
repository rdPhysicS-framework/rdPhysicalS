#ifndef	__APPLICATION_RT_H__
#define	__APPLICATION_RT_H__

#include "../../GlobalDefs.h"
#include "../ClGlobalDef.h"
#include "../../rdps-package/ArrayBuffer.h"

RDPS_BEGIN

	CL_BEGIN
		/******************************************************************************************************************************************
		 *
		 * Classe que contem os componentes para para o Programa OpenCL.
		 * Responsavel em Criar o programa, fazer build, enviar os dados 
		 * para serem lidos ou escritos, dar comando para o processamento da dados.
		 * Mas, ela n�o pode se criar necessita de um terceiro pra cria-l�, 
		 * pois necessida que seja definida a platform e device da platform que ser� usado, 
		 * e passar o arquivo openCl ja carredo. A partir ela cria o restante no 
		 * CreateProgram(const std::string &source).
		 * 
		 ******************************************************************************************************************************************/
		class ApplicationRT 
		{
		private:
			friend class ApplicationRTBuilder;

		private:
			PlatformComponent *platform;
			DeviceComponent *device;
			ContextComponent *context;
			CommmandQueueComponent *queue;
			ProgramComponent *program;
			KernelComponent *kernel;
			ItensWorkGroupComponent itens;

		private:
			std::vector<MemObjectComponent*> buffers;
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padr�o
			 * Inicializa todos os conteudos dos componentes em nullptr
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT();
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Recebe a platform e device para a cria��o do programa
			 * o restante inicializa seus conteudos em nullptr
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT(const PlatformComponent &_platform,
						  const DeviceComponent &_device);

			inline ApplicationRT &CreateContext();
			inline ApplicationRT &CreateCommandQueue();
	
		public:

			~ApplicationRT();
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor Padr�o
			 *--------------------------------------------------------------------------------------------------------------------------------------*/

			 /*-------------------------------------------------------------------------------------------------------------------------------------
			  * D� o comando de cria��o do programa program.CreateProgra(source)
			  *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &CreateProgram(const std::string &source);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * D� o comando de cria��o da referencia da fu��o kernel kernel.CreateKernel(name)
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &CreateKernel(const std::string &name);

			inline PlatformComponent *GetPlatform() const		 { return platform; }
			inline DeviceComponent *GetDevice() const			 { return device;   }
			inline ContextComponent *GetContext() const			 { return context;  }
			inline CommmandQueueComponent *GetQueue() const		 { return queue;    }
			inline ProgramComponent *GetProgram() const			 { return program;  }
			inline KernelComponent *GetKernel() const			 { return kernel;   }
			inline std::vector<MemObjectComponent*> &GetBuffers() { return buffers;  }
			const ItensWorkGroupComponent &GetItens() const		 { return itens;    }

			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Cria o buffer (MemObjectComponent) e adiciona na lista de memObjects,
			 * retornando o id do objeto na lista, para que posteriormente seja adicionado novamente
			 * os dados na lista.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			int CreateBuffer(const PKG ArrayBuffer<T> &bf);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * retorna uma string contendo as informa��es do componente desejado
			 * ou de todos.
			 * Exemplo:
			 * GetInfo(KERNEL_COMPONENETE) returna as informa��es do kernel
			 * GetInfo(ALL_COMPONENTES) retorna as informa��es de todos os componenetes
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			std::string GetInfo(const ComponentCL type) const;
			int GetBuffer();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que verifica se no local desejado (lacation) na lista se est� disponivel, se estiver
			 * retorna o lacation. Se n�o, retorna um valor negativo.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			int GetBuffer(const int location);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que adiciona a platforma
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetPlatform(const PlatformComponent &_platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que adiona o device
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetDevice(const DeviceComponent &_device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que adiciona os itens de trabalho
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetItensWorkGroup(const ItensWorkGroupComponent &itens);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que destroy todos os buffer, chama a fun��o Release() de cada um,
			 * mas n�o limpa a lista de buffers para posteriormente serem injetados novos dados.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			void DestroyBuffer(const int id);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que destroy todos os componentes chamando a fun��o Release() de cada um.
			 * Essa fun��o limpa a lista de buffers.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			void DestroyApp();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que seta um argumento no kernel passando o id como parametro
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &ApplyArgument(const int id);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			* Fun��o que seta todos os argumentos no kernel
			*-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &ApplyArguments();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o que seta varios argumentos(apenas os necessarios) no kernel sem a necessidade de ser em ordem.
			 * Exemplo:
			 * ApplyArguments({1, 4, 5, 10});
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &ApplyArguments(const std::initializer_list<uint> index);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o responsavel em dar o comando de escrita de dados ou leitura de dados
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			ApplicationRT &ApplyBuffer(PKG ArrayBuffer<T> &bf);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o responsavel em dar o comando de passar para o kernel os dados que ser�o 
			 * copiados. Fun��o generica pois, pode se dados de qualquer tipo. Esses tipos de dados
			 * para n� precis�o de ArrayBuffer.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline ApplicationRT &PassDataCopy(const int id, T *data, const size_t size);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o Respossavel em dar o comando para o processamento de dados no dispositivo.
			 * recebe um bool como parametro, se for true renveia todos os argumentos
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &Process(const bool applyEverything = false);
		};

		template<class T>
		inline int ApplicationRT::CreateBuffer(const PKG ArrayBuffer<T> &bf)
		{
			if (bf.GetId() <= ARRAY_WITHOUT_INDEX)
			{
				MemObjectComponent *mem = new MemObjectComponent(*context, bf.GetTypeAction(), bf.GetBytes());
				buffers.push_back(mem);
				return (buffers.size() - 1);
			}
			
			int id = GetBuffer(bf.GetId()); 
			if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
			{
				Logger::Log("ERROR requested index invalidates " +
							(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
			}

			*buffers[id] = MemObjectComponent(*context, bf.GetTypeAction(), bf.GetBytes());
			
			return id;
		}

		template<class T>
		inline ApplicationRT &ApplicationRT::ApplyBuffer(PKG ArrayBuffer<T> &bf)
		{
			if (bf.GetTypeAction() == RETURN_DATA_WRITING)
			{
				int id = bf.GetId();// GetBuffer(bf.GetId());
				
				if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
				{
					Logger::Log("ERROR requested index invalidates " +
								(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
				}

				queue->WriteBuffer((*buffers[id]), bf.GetBytes(), bf.GetElement());
			}
			else if(bf.GetTypeAction() == RETURN_DATA_READING)
			{
				int id = bf.GetId();//GetBuffer(bf.GetId());
				if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
				{
					Logger::Log("ERROR requested index invalidates " +
								(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
				}

				queue->ReadBuffer((*buffers[id]), bf.GetBytes(), bf.GetElement());
			}

			return (*this);
		}

		template<class T>
		inline ApplicationRT &ApplicationRT::PassDataCopy(const int id, T *data, const size_t size)
		{
			size_t bytes = sizeof(T) * size;
			kernel.SetArgument(id, data, bytes);
			return (*this);
		}
	CL_END
RDPS_END

#endif//__APPLICATION_CL_H__