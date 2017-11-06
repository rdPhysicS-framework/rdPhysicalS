#ifndef	__LOADER_FILES__
#define	__LOADER_FILES__

#include <string>
#include "..\rdps-CL\ClGlobalDef.h"

RDPS_BEGIN
	CL_BEGIN
	   /********************************************************************************
		*
		*Classe para auxiliar na carga de arquivos openCl
		*
		********************************************************************************/
		class LoaderFiles
		{
		public:
			/*--------------------------------------------------------------------------
			 *Função que possibilita carregar varios arquivos passando 
			 *como parametro uma lista de endereços, retornando uma 
			 *string contendo todos os conteudos dos arquivos.
			 *exemplo:
			 *std::string aux = LoadSource({"teste1.txt", "teste2.txt"});
			 *--------------------------------------------------------------------------*/
			static std::string LoadSource(std::initializer_list<std::string> files);
			
			/*---------------------------------------------------------------------------
			 *Função para Carregar apenas um arquivo pelo seu endereço,
			 * retornando uma string com o conteudo do arquivo.
			 *---------------------------------------------------------------------------*/
			static std::string ReadInputStream(std::string name);
		};
	CL_END
RDPS_END

#endif//__LOADER_FILES__