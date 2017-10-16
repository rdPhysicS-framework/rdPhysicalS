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
		 * Classe responsavel em criar a Aplica��o OpenCL (ApplicationRT).
		 * Carrega o codigo openCL no arquivo, Cria a aplica��o, adiciona
		 * a plataform, o device, adiciona a fun��o kernel, e retorna a aplica��o
		 *
		 *******************************************************************************************************************************************/
		class ApplicationRTBuilder
		{
		private:
			ApplicationRT *app;

		public:
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor Padr�o
			 * Inicializa a aplica��o com o contrutor padr�o
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padr�o 
			 * N�o faz nada
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			~ApplicationRTBuilder();
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que adiciona a plataform na aplica��o
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddPlatform(const PlatformComponente &platform);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que adiciona o device na aplica��o
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddDevice(const DeviceComponente &device);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que adiciona os valores referentes aos itens de 
			 * trabalho na aplica��o
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddItensWorkGroup(const ItensWorkGroupComponente &itens);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que d� o comando para a aplica��o de criar o kernel atraves 
			 * de uma string que contem o nome da fun��o.
			 * Obs: O nome precisar ser o mesmo que est� no c�digo openCL do arquivo,
			 * para que seja bem sucedido;
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &AddFunctionKernel(const std::string &name);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar que carrega um ou mais arquivos para a aplica��o
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			ApplicationRTBuilder &LoadProgram(const std::initializer_list<std::string> files);
			/*-------------------------------------------------------------------------------------------------------------------------------------
			 * Fun��o auxiliar para retorno do aplicativo.
			 * Exemplo:
			 * ApplicationRT app = build.Create();
			 *-------------------------------------------------------------------------------------------------------------------------------------*/
			inline ApplicationRT *Create() const { return app; }
		};

	CL_END
RDPS_END


#endif//__APPLICATION_BUILDER_H__