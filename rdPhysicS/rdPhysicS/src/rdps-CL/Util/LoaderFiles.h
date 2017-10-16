#ifndef	__LOADER_FILES__
#define	__LOADER_FILES__

#include <string>

namespace rdps 
{
	namespace Cl
	{
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
	}
}

#endif//__LOADER_FILES__