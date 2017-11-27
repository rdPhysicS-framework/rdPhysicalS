#ifndef	__APPLICATION_RT_H__
#define	__APPLICATION_RT_H__

#include "../../GlobalDefs.h"
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
		class ApplicationCLBuilder;
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
			friend ApplicationCLBuilder;

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
			PlatformComponent *GetPlatform() const;
			DeviceComponent *GetDevice() const;
			ContextComponent *GetContext() const;
			CommmandQueueComponent *GetQueue() const;
			ProgramComponent *GetProgram() const;
			KernelComponent *GetKernel() const;
			const std::vector<MemObjectComponent*> &GetBuffers() const;
			ItensWorkGroupComponent *GetItens() const;

			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Cria o buffer (MemObjectComponent) e adiciona na lista de memObjects,
			 * retornando o id do objeto na lista, para que posteriormente seja adicionado novamente
			 * os dados na lista.
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			int CreateBuffer(const int id, const ActionFile typeAction, const size_t bytes);
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
			ApplicationCL &ApplyBuffer(const int id, const ActionFile typeAction, const size_t bytes, void *data);
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
		inline ApplicationCL &ApplicationCL::PassDataCopy(const int id, T *data)
		{
			kernel->SetArgument(id, (const void*)data, sizeof(T));
			return (*this);
		}

	CL_END
RDPS_END

#endif//__APPLICATION_CL_H__