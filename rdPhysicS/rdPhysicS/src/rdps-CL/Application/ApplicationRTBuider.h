#ifndef	__APPLICATION_BUILDER_H__
#define	__APPLICATION_BUILDER_H__

#include "../../GlobalDefs.h"
#include <string>

RDPS_BEGIN
	CL_BEGIN
		class ApplicationRT;
		class PlatformComponente;
		class DeviceComponente;
		class ItensWorkGroupComponente;

		/*******************************************************************************************************************************************
		 *
		 * Classe responsavel em criar a Aplicação OpenCL (ApplicationRT).
		 * Carrega o codigo openCL no arquivo, Cria a aplicação, adiciona
		 * a plataform, o device, adiciona a função kernel, e retorna a aplicação
		 *
		 *******************************************************************************************************************************************/
		class ApplicationRTBuilder
		{
		private:
			ApplicationRT *app;

		public:
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padrão
			 * Inicializa a aplicação com o contrutor padrão
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrão 
			 * Não faz nada
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			~ApplicationRTBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona a plataform na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddPlatform(const PlatformComponente &platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona o device na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddDevice(const DeviceComponente &device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que adiciona os valores referentes aos itens de 
			 * trabalho na aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddItensWorkGroup(const ItensWorkGroupComponente &itens);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que dá o comando para a aplicação de criar o kernel atraves 
			 * de uma string que contem o nome da função.
			 * Obs: O nome precisar ser o mesmo que está no código openCL do arquivo,
			 * para que seja bem sucedido;
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddFunctionKernel(const std::string &name);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que carrega um ou mais arquivos para a aplicação
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &LoadProgram(const std::initializer_list<std::string> files);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar para retorno do aplicativo.
			 * Exemplo:
			 * ApplicationRT app = build.Create();
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			inline ApplicationRT *Create() const { return app; }
		};

	CL_END
RDPS_END


#endif//__APPLICATION_BUILDER_H__