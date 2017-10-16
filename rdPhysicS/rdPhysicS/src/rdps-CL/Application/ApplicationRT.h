#ifndef	__APPLICATION_RT_H__
#define	__APPLICATION_RT_H__

#include "../ClGlobalDef.h"
#include "../../rdps-package/ArrayBuffer.h"

RDPS_BEGIN

	CL_BEGIN
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
		class ApplicationRT 
		{
		private:
			friend class ApplicationRTBuilder;

		private:
			PlatformComponente platform;
			DeviceComponente device;
			ContextComponente context;
			CommmandQueueComponente queue;
			ProgramComponente program;
			KernelComponente kernel;
			std::vector<MemObjectComponente> buffers;
			ItensWorkGroupComponente itens;

		private:
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padrão
			 * Inicializa todos os conteudos dos componentes em nullptr
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT();
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor
			 * Recebe a platform e device para a criação do programa
			 * o restante inicializa seus conteudos em nullptr
			 *--------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT(const PlatformComponente &_platform,
						  const DeviceComponente &_device);

			inline void CreateContext() { context = ContextComponente(device); }
			inline void CreateCommandQueue() { queue = CommmandQueueComponente(context, device); }
	
		public:

			~ApplicationRT();
			/*--------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor Padrão
			 *--------------------------------------------------------------------------------------------------------------------------------------*/

			 /*-------------------------------------------------------------------------------------------------------------------------------------
			  * Dá o comando de criação do programa program.CreateProgra(source)
			  *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &CreateProgram(const std::string &source);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Dá o comando de criação da referencia da fução kernel kernel.CreateKernel(name)
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &CreateKernel(const std::string &name);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Cria o buffer (MemObjectComponente) e adiciona na lista de memObjects,
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
			std::string GetInfo(const InfoComponenteCL type) const;
			int GetBuffer();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que verifica se no local desejado (lacation) na lista se está disponivel, se estiver
			 * retorna o lacation. Se não, retorna um valor negativo.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			int GetBuffer(const int location);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiciona a platforma
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetPlatform(const PlatformComponente &_platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiona o device
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetDevice(const DeviceComponente &_device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que adiciona os itens de trabalho
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &SetItensWorkGroup(const ItensWorkGroupComponente &itens);
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
			ApplicationRT &ApplyArgument(const int id);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			* Função que seta todos os argumentos no kernel
			*-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &ApplyArguments();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função que seta varios argumentos(apenas os necessarios) no kernel sem a necessidade de ser em ordem.
			 * Exemplo:
			 * ApplyArguments({1, 4, 5, 10});
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRT &ApplyArguments(const std::initializer_list<uint> index);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função responsavel em dar o comando de escrita de dados ou leitura de dados
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			ApplicationRT &ApplyBuffer(PKG ArrayBuffer<T> &bf);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função responsavel em dar o comando de passar para o kernel os dados que serão 
			 * copiados. Função generica pois, pode se dados de qualquer tipo. Esses tipos de dados
			 * para nã precisão de ArrayBuffer.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			template<class T>
			inline ApplicationRT &PassDataCopy(const int id, T *data, const size_t size);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função Respossavel em dar o comando para o processamento de dados no dispositivo.
			 * recebe um bool como parametro, se for true renveia todos os argumentos
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			void Process(const bool applyEverything = false);
		};

		template<class T>
		inline int ApplicationRT::CreateBuffer(const PKG ArrayBuffer<T> &bf)
		{
			if (bf.GetId() <= ARRAY_WITHOUT_INDEX)
			{
				MemObjectComponente mem = MemObjectComponente(context, bf.GetTypeAction(), bf.GetBytes());
				buffers.push_back(mem);
				return buffers.size() - 1;
			}
			
			int id = GetBuffer(bf.GetId()); 
			if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
			{
				Logger::Log("ERROR requested index invalidates "
					(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
			}

			buffers[id] = MemObjectComponente(context, bf.GetTypeAction(), bf.GetBytes());
			
			return id;
		}

		template<class T>
		inline ApplicationRT &ApplicationRT::ApplyBuffer(PKG ArrayBuffer<T> &bf)
		{
			if (bf.GetTypeAction() == RETURN_DATA_WRITING)
			{
				int id = GetBuffer(bf.GetId());
				if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
				{
					Logger::Log("ERROR requested index invalidates "
						(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
				}

				queue.WriteBuffer(buffers[id], bf.GetBytes(), bf.GetElement());
			}
			else if(bf.GetTypeAction() == RETURN_DATA_WRITING)
			{
				int id = GetBuffer(bf.GetId());
				if (id == EMPTY_BUFFER || id == BUSY_LOCATION)
				{
					Logger::Log("ERROR requested index invalidates "
						(id == EMPTY_BUFFER) ? "empty array." : "busy location.");
				}

				queue.ReadBuffer(buffers[id], bf.GetBytes(), bf.GetElement());
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