#ifndef	__MESSAGE_H__
#define	__MESSAGE_H__

#include "..\..\GlobalDefs.h"
#include <string>

RDPS_BEGIN
	PDCT_BEGIN

		class Entity;

		class Message
		{
		private:
			Entity *sender;
			Entity *receiver;
			std::string message;
			void *data;

		public:
			Message(Entity *msgSender,
					Entity *msgReceiver,
					const std::string msg,
					void *_data = nullptr);
			Message(const Message &other);
			~Message();

			inline Entity *GetSender() const { return sender; }
			inline Entity *GetReceiver() const { return receiver; }
			const std::string &GetMessage() const { return message; }
			void *GetData() const { return data; }

			Message &SetSender(Entity *_sender);
			Message &SetReceiver(Entity *_receiver);
			Message &SetMessage(const std::string msg);
			Message &SetData(void *_data);

			Message &operator=(const Message &other);
		};

	PDCT_END
RDPS_END

#endif//__MESSAGE_H__