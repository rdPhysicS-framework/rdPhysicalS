#ifndef	 __APPLICATION_CL_FACTOR_H__
#define	 __APPLICATION_CL_FACTOR_H__

#include "..\..\GlobalDefs.h"
#include <string>

RDPS_BEGIN
	CL_BEGIN
	class ApplicationCL;
	/************************************************************************************************************************************
	 *
	 * Classe respons�vel em dar o comando para criar a aplica��o openCL.
	 * processa todos os dados respons�veis para cria��o da aplica��o e passa 
	 * para o ApplicationCLBuider.
	 *
	 ************************************************************************************************************************************/
	class ApplicationCLFactor
	{
	private:
		/*-------------------------------------------------------------------------------------------------------------------------------
		 * Fun��o auxiliar que retorna o input do usuario.
		 *-------------------------------------------------------------------------------------------------------------------------------*/
		static uint GetOptions(uint size);

	public:
		/*-------------------------------------------------------------------------------------------------------------------------------
		 * Fun��o auxiliar que cria a aplicacao atravez do input do usuario.
		 * Atraves do console mostrara todas as plataformas e dispositivos 
		 * existentes no computador. E o usuario escolhera entre eles para
		 * que seja criado a aplicacao.
		 *-------------------------------------------------------------------------------------------------------------------------------*/
		static ApplicationCL *CreateApplicationUsersInput();
	};
	CL_END
RDPS_END

#endif //__APPLICATION_CL_FACTOR_H__