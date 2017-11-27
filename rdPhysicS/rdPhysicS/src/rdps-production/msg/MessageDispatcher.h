#ifndef	__MESSAGE_DISPATCHER_H__
#define	__MESSAGE_DISPATCHER_H__

#include "..\..\GlobalDefs.h"
#include <string>
RDPS_BEGIN
	PDCT_BEGIN

		class Message;
		class Entity;
		/********************************************************************************************************************************************
		 *
		 * Classe Resposavel em enviar as mesnsagens.
		 * Ela eh static para facilitar o acesso para o envio
		 * das mensagens.
		 *
		 ********************************************************************************************************************************************/
		class MessageDispatcher
		{
		private:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que envia as mensagens
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static void DeliverMessage(Entity *receiver,
									   const Message &message);

		public:
			/*---------------------------------------------------------------------------------------------------------------------------------------
			 * Funcao auxiliar que instancia a menssagem e da o comando de envio.
			 * recebe como parametro Entity *sender que eh quem esta enviando,
			 * Entity *receiver que eh que ira receber,
			 * const std::string message que eh a mensagem,
			 * void *data que eh os dados extras para possivelmente serem processados,
			 * por padrao eh nulo.
			 *---------------------------------------------------------------------------------------------------------------------------------------*/
			static void DispatchMessage(Entity *sender,
										Entity *receiver,
										const std::string message,
										void *data = nullptr);
		};

	PDCT_END
RDPS_END

#endif//__MESSAGE_DISPATCHER_H__