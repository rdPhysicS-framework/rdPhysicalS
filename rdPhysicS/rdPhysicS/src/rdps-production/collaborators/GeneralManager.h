#ifndef	__GENERAL_MANAGER_H__
#define	__GENERAL_MANAGER_H__

#include "..\base\Entity.h"
#include <map>

RDPS_BEGIN
	PDCT_BEGIN
		
		class Collaborator;

		/********************************************************************************************************************************************
		 *
		 * Classe Resposavel em gerenciar os colaboradores e os designar para as suas
		 * funcoes, atraves das mensagens. Nela consiste:
		 * -> map contendo todos os colaboradores;
		 * -> um intancia do proprio objeto para facilitar o acesso em outras classe,
		 *    e evitar novas instancias fora dela.
		 *
		 * Herda da classe Entity para receber e enviar mensagens
		 *
		 ********************************************************************************************************************************************/
		class GeneralManager : public Entity
		{
		private:
			std::map<CollaboratorsFunction, 
					 Collaborator*> collaborators;

			static GeneralManager *INSTANCE;
		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 * privado para ser instanciado internamente apenas uma vez
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			GeneralManager();

			GeneralManager(const GeneralManager &other);
		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 * apenas se destroi
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~GeneralManager();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar static para retorno|criacao da instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static GeneralManager *Get();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna um colaborador da std::map pela
			 * sua funcao
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const Collaborator
				*GetCollaborator(const CollaboratorsFunction function);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a lista de colaboradores
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const std::map<CollaboratorsFunction, Collaborator*>
				&GetCollaborators() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que adiciona um colaborador na lista
			 * recebe como parametro o id (hash) que eh a funcao do colaborador e um colabordor
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			GeneralManager &AddCollaborator(CollaboratorsFunction function,
											Collaborator *collaborator);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que remove um colaborador da lista
			 * recebe como parametro o id (hash) que eh a funcao do colaborador
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			GeneralManager &RemoveCollaborator(CollaboratorsFunction function);
			
			//GeneralManager *Clone();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que executa a funcao do gerente
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual GeneralManager &ExecuteFunction();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao que trata as mensagens recebidas
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__GENERAL_MANAGER_H__