#ifndef	__APPLICATION_BUILDER_H__
#define	__APPLICATION_BUILDER_H__

#include "../../GlobalDefs.h"
#include <string>

RDPS_BEGIN
	CL_BEGIN
		class ApplicationCL;
		class PlatformComponent;
		class DeviceComponent;
		class ItensWorkGroupComponent;

		/*******************************************************************************************************************************************
		 *
		 * Classe responsavel em criar a Aplicação OpenCL (ApplicationCL).
		 * Carrega o codigo openCL no arquivo, Cria a aplicação, adiciona
		 * a plataform, o device, adiciona a função kernel, e retorna a aplicação
		 *
		 *******************************************************************************************************************************************/
		class ApplicationCLBuilder
		{
		private:
			ApplicationCL *app;

		public:
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padrão
			 * Inicializa a aplicação com o contrutor padrão
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrão 
			 * Não faz nada
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			~ApplicationCLBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona a plataform na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder &AddPlatform(const PlatformComponent &platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona o device na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder &AddDevice(const DeviceComponent &device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona os valores referentes aos itens de 
			 * trabalho na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder &AddItensWorkGroup(const ItensWorkGroupComponent &itens);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que dá o comando para a aplicação de criar o kernel atraves 
			 * de uma string que contem o nome da função.
			 * Obs: O nome precisar ser o mesmo que está no código openCL do arquivo,
			 * para que seja bem sucedido;
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder &AddFunctionKernel(const std::string &name);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que carrega um ou mais arquivos para a aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationCLBuilder &LoadProgram(const std::initializer_list<std::string> &files);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar para retorno do aplicativo.
			 * Exemplo:
			 * ApplicationCL app = build.Create();
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			inline ApplicationCL *Create() const { return app; }
		};

	CL_END
RDPS_END


#endif//__APPLICATION_BUILDER_H__