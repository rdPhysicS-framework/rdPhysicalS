#ifndef	__MESSAGE_DISPATCHER_H__
#define	__MESSAGE_DISPATCHER_H__

#include "..\..\GlobalDefs.h"
#include <string>
RDPS_BEGIN
	PDCT_BEGIN

		class Message;
		class Entity;

		class MessageDispatcher
		{
		private:
			static void DeliverMessage(Entity *receiver,
									   const Message &message);

		public:
			static void DispatchMessage(Entity *sender,
										Entity *receiver,
										const std::string message,
										void *data = nullptr);
		};

	PDCT_END
RDPS_END

#endif//__MESSAGE_DISPATCHER_H__