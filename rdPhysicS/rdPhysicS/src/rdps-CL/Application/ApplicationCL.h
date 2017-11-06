#ifndef	__APPLICATION_RT_H__
#define	__APPLICATION_RT_H__

#include "../../GlobalDefs.h"
#include "../../rdps-packages/ArrayBuffer.h"
#include <vector>

RDPS_BEGIN

	CL_BEGIN

		class PlatformComponent;
		class DeviceComponent;
		class ContextComponent;
		class CommmandQueueComponent;
		class ProgramComponent;
		class KernelComponent;
		class MemObjectComponent;
		class ItensWorkGroupComponent;
		
		/******************************************************************************************************************************************
		 *
		 * Classe que contem os componentes para para o Programa OpenCL.
		 * Responsavel em Criar o programa, fazer build, enviar os dados 
		 * para serem lidos ou escritos, dar comando para o processamento da dados.
		 * Mas, ela não pode se criar necessita de um terceiro pra cria-lá, 
		 * pois necessida que seja definida a platform e device da platform que será usado, 
		 * e passar o arquivo openCl ja carredo. A partir ela cria o restante no 
		 * CreateProgram(const std::string &source).
		 * 
		 ******************************************************************************************************************************************/
		class ApplicationCL 
		{
		private:
			friend class ApplicationCLBuilder;

		private:
			PlatformComponent *platform;
			DeviceComponent *device;
			ContextComponent *context;
			CommmandQueueComponent *queue;
			ProgramComponent *program;
			KernelComponent *kernel;
			ItensWorkGroupComponent *itens;
			std::vector<MemObjectComponent*> buffers;

		private:
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padrão
			 * Inicializa todos os conteudos dos componentes em nullptr
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL();
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Recebe a platform e device para a criação do programa
			 * o restante inicializa seus conteudos em nullptr
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL(const PlatformComponent &_platform,
						  const DeviceComponent &_device);

			ApplicationCL &CreateContext();
			ApplicationCL &CreateCommandQueue();
	
			 /*-------------------------------------------------------------------------------------------------------------------------------------
			  * Dá o comando de criação do programa program.CreateProgra(source)
			  *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &CreateProgram(const std::string &source);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Dá o comando de criação da referencia da fução kernel kernel.CreateKernel(name)
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &CreateKernel(const std::string &name);

		public:
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor Padrão
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			~ApplicationCL();

			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Funcoes de acesso
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			inline PlatformComponent *GetPlatform() const		     { return platform; }
			inline DeviceComponent *GetDevice() const			     { return device;   }
			inline ContextComponent *GetContext() const			     { return context;  }
			inline CommmandQueueComponent *GetQueue() const		     { return queue;    }
			inline ProgramComponent *GetProgram() const			     { return program;  }
			inline KernelComponent *GetKernel() const			     { return kernel;   }
			inline std::vector<MemObjectComponent*> &GetBuffers()    { return buffers;  }
			inline ItensWorkGroupComponent *GetItens() const		 { return itens;    }

			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Cria o buffer (MemObjectComponent) e adiciona na lista de memObjects,
			 * retornando o id do objeto na lista, para que posteriormente seja adicionado novamente
			 * os dados na lista.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			int CreateBuffer(const PKG ArrayBuffer<T> &bf);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * retorna uma string contendo as informações do componente desejado
			 * ou de todos.
			 * Exemplo:
			 * GetInfo(KERNEL_COMPONENETE) returna as informações do kernel
			 * GetInfo(ALL_COMPONENTES) retorna as informações de todos os componenetes
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			std::string GetInfo(const ComponentCL type) const;
			int GetBuffer();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que verifica se no local desejado (lacation) na lista se está disponivel, se estiver
			 * retorna o lacation. Se não, retorna um valor referente a condição (ocupado ou array vazio).
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			int GetBuffer(const int location);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiciona a platforma
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &SetPlatform(const PlatformComponent &_platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiona o device
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &SetDevice(const DeviceComponent &_device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiciona os itens de trabalho
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &SetItensWorkGroup(const ItensWorkGroupComponent &itens);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que destroy todos os buffer, chama a função Release() de cada um,
			 * mas não limpa a lista de buffers para posteriormente serem injetados novos dados.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			void DestroyBuffer(const int id);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que destroy todos os componentes chamando a função Release() de cada um.
			 * Essa função limpa a lista de buffers.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			void DestroyApp();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que seta um argumento no kernel passando o id como parametro
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &ApplyArgument(const int id);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			* Função que seta todos os argumentos no kernel
			*-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &ApplyArguments();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que seta varios argumentos(apenas os necessarios) no kernel sem a necessidade de ser em ordem.
			 * Exemplo:
			 * ApplyArguments({1, 4, 5, 10});
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &ApplyArguments(const std::initializer_list<uint> index);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função responsavel em dar o comando de escrita de dados ou leitura de dados
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			ApplicationCL &ApplyBuffer(PKG ArrayBuffer<T> &bf);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função responsavel em dar o comando de passar para o kernel os dados que serão 
			 * copiados. Função generica pois, pode se dados de qualquer tipo. Esses tipos de dados
			 * para nã precisão de ArrayBuffer.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline ApplicationCL &PassDataCopy(const int id, T *data);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função Respossavel em dar o comando para o processamento de dados no dispositivo.
			 * recebe um bool como parametro, se for true renveia todos os argumentos
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCL &Process(const bool applyEverything = false);
		};

		template<class T>
		inline int ApplicationCL::CreateBuffer(const PKG ArrayBuffer<T> &bf)
		{
			if (bf.GetId() <= ARRAY_WITHOUT_INDEX)
			{
				MemObjectComponent *mem = new MemObjectComponent(*context, bf.GetTypeAction(), bf.GetBytes());
				buffers.push_back(mem);
				return static_cast<int>(buffers.size() - 1);
			}
			
			int id = GetBuffer(bf.GetId()); 
			if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
			{
				Logger::Log((id == EMPTY_BUFFER) ? 
							"ERROR: list of objects of memory empty.\n" : 
							"ERROR requested index invalidates busy location.\n");
			}

			*buffers[id] = MemObjectComponent(*context, bf.GetTypeAction(), bf.GetBytes());
			
			return id;
		}

		template<class T>
		inline ApplicationCL &ApplicationCL::ApplyBuffer(PKG ArrayBuffer<T> &bf)
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
		inline ApplicationCL &ApplicationCL::PassDataCopy(const int id, T *data)
		{
			kernel.SetArgument(id, data, sizeof(T));
			return (*this);
		}

	CL_END
RDPS_END

#endif//__APPLICATION_CL_H__