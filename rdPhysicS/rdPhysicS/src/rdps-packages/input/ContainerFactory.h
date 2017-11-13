#ifndef	__CONTAINER_FACTORY_H__
#define	__CONTAINER_FACTORY_H__

#include <string>
#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	PKG_BEGIN

		class PackageBase;
		class Container;
		/************************************************************************************************************************************
		 *
		 * Classe responsável em dar o comando para criar o Container de pacotes.
		 * processa todos os dados responsáveis para criação do conteiner e passa
		 * para o ContainerBuider.
		 *
		 ************************************************************************************************************************************/
		class ContainerFactory
		{
		public:
			/*-------------------------------------------------------------------------------------------------------------------------------
			 * Função auxiliar que cria o Container atraves dois parametros:
			 * -> o primeiro eh a lista do nome de cada pacote;
			 * -> o segundo eh a lista de pacotes.
			 *-------------------------------------------------------------------------------------------------------------------------------*/
			static Container *CreateContainer(std::initializer_list<std::string>  _ids,
											  std::initializer_list<PackageBase*> _pkgs);
			static Container *CreateContainer();
		};

	PKG_END
RDPS_END

#endif//__CONTAINER_FACTORY_H__