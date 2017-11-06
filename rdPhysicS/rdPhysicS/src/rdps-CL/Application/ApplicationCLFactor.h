#ifndef	 __APPLICATION_CL_FACTOR_H__
#define	 __APPLICATION_CL_FACTOR_H__

#include "..\..\GlobalDefs.h"
#include <string>

RDPS_BEGIN
	CL_BEGIN
	class ApplicationCL;
	/************************************************************************************************************************************
	 *
	 * Classe responsável em dar o comando para criar a aplicação openCL.
	 * processa todos os dados responsáveis para criação da aplicação e passa 
	 * para o ApplicationCLBuider.
	 *
	 ************************************************************************************************************************************/
	class ApplicationCLFactor
	{
	private:
		/*-------------------------------------------------------------------------------------------------------------------------------
		 * Função auxiliar que retorna o input do usuario.
		 *-------------------------------------------------------------------------------------------------------------------------------*/
		static uint GetOptions(uint size);

	public:
		/*-------------------------------------------------------------------------------------------------------------------------------
		 * Função auxiliar que cria a aplicacao atravez do input do usuario.
		 * Atraves do console mostrara todas as plataformas e dispositivos 
		 * existentes no computador. E o usuario escolhera entre eles para
		 * que seja criado a aplicacao.
		 *-------------------------------------------------------------------------------------------------------------------------------*/
		static ApplicationCL *CreateApplicationUsersInput();
	};
	CL_END
RDPS_END

#endif //__APPLICATION_CL_FACTOR_H__