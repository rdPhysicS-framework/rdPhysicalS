#ifndef	__COLLABORATOR_H__
#define	__COLLABORATOR_H__

#include "Entity.h"

RDPS_BEGIN
	PDCT_BEGIN

		class StateMachine;

		/********************************************************************************************************************************************
		 *
		 * Classe Base para todos os colaboradores internos da aplica��o que fazem tudo funcionar
		 * Nela consiste:
		 * -> CollaboratorsFunction: a fun��o de cada colaborador;
		 * -> StateMachine: maquina de estados para controle dos estados de cada colaborador.
		 * 
		 * Todos devem herdar deta classe para um melhor gerenciamento de colaboradores.
		 * Essa classe herda da classe Entity pois ocorre troca de mensagem entre os colaboradores.
		 *
		 ********************************************************************************************************************************************/
		class Collaborator : public Entity
		{
		protected:
			CollaboratorsFunction function;
			StateMachine *stateMachine;

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor 
			 * recebe como parametro um enum que � a fun��o do colaborador
			 * para melhor distribuicao das fun��es pelo gerenciador.
			 * E inicializa a maquina de estados.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Collaborator(const CollaboratorsFunction _function,
						 StateMachine *_stateMachine);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor de copia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			Collaborator(const Collaborator &other);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padr�o para destruir a StateMachine
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual ~Collaborator();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a funcao do colaborador
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			const CollaboratorsFunction GetFunction() const;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna a StateMachine
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			StateMachine *GetStateMachine() const;

			virtual Collaborator *Clone() = 0;
			virtual Collaborator &Init() = 0;
			virtual Collaborator &ExecuteFunction() = 0;
			virtual Collaborator &Exit() = 0;
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao que trata as mensagens recebidas
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__COLLABORATOR_H__