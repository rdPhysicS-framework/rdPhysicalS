#ifndef	__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__
#define	__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class ObjectDispatcher;

		/********************************************************************************************************************************************
		 *
		 * Classe Referente ao estado do ObjectDispatcher,
		 * Nela que ocorre o envio dos dados.
		 * Nela consite:
		 * -> static State<ObjectDispatcher> *INSTANCE: que eh uma referencia
		 *    dela mesmo, para facilitar o acesso e otimizar o processo evitando
		 *    inumeras instancias. 
		 *
		 ********************************************************************************************************************************************/
		class ToSendObjectsForTheDevice : public State<ObjectDispatcher>
		{
		private:
			static State<ObjectDispatcher> *INSTANCE;

		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Construtor padrao
			 * privado pois só pode ter um instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			ToSendObjectsForTheDevice();

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Destrutor padrao destroi a instancia
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			~ToSendObjectsForTheDevice();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que retorna|cria a instancia 
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static State<ObjectDispatcher> *Get();
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para inicializacao dos dados do objeto que
			 * possui esse estado, quando entra neste estado
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Enter(const ObjectDispatcher &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para execucao da funcao do estado
			 * (Enviar os dados)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Execute(const ObjectDispatcher &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para sair do estado (o que faz quando sai)
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual void Exit(const ObjectDispatcher &c);
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar para tratar as menssagens recebidas
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			virtual bool OnMessage(const ObjectDispatcher &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__