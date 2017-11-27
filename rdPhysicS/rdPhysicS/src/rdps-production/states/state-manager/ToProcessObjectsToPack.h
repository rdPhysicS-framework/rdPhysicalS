#ifndef	__TO_PROCESS_OBJECT_TO_PACK_H__
#define	__TO_PROCESS_OBJECT_TO_PACK_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class ManagerObjects;

		/********************************************************************************************************************************************
		 *
		 * Classe Referente ao estado do ManagerObjects,
		 * Nela que ocorre o envio dos dados.
		 * Nela consite:
		 * -> static State<ManagerObjects> *INSTANCE: que eh uma referencia
		 *    dela mesmo, para facilitar o acesso e otimizar o processo evitando
		 *    inumeras instancias. 
		 *
		 ********************************************************************************************************************************************/
		class ToProcessObjectsToPack : public State<ManagerObjects>
		{
		private:
			static State<ManagerObjects> *INSTANCE;

		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 * privado pois só pode ter um instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ToProcessObjectsToPack();

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao destroi a instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~ToProcessObjectsToPack();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna|cria a instancia 
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static State<ManagerObjects> *Get();

			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para inicializacao dos dados do objeto que
			 * possui esse estado, quando entra neste estado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Enter(const ManagerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para execucao da funcao do estado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Execute(const ManagerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para sair do estado (o que faz quando sai)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Exit(const ManagerObjects &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para tratar as menssagens recebidas
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual bool OnMessage(const ManagerObjects &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_PROCESS_OBJECT_TO_PACK_H__