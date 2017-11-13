#include "Message.h"
#include "..\base\Entity.h"

USING_RDPS
USING_PDCT

Message::Message(Entity *msgSender, 
				 Entity *msgReceiver, 
				 const std::string msg, 
				 void *_data) :
		 sender(msgSender),
		 receiver(msgReceiver),
		 message(msg),
		 data(_data)
{}

Message::Message(const Message &other) :
		 sender(other.sender),
		 receiver(other.receiver),
		 message(other.message),
		 data(other.data)
{}

Message::~Message()
{}

Message &Message::SetSender(Entity *_sender)
{
	sender = _sender;
	return (*this);
}

Message &Message::SetReceiver(Entity *_receiver)
{
	receiver = _receiver;
	return (*this);
}

Message &Message::SetMessage(const std::string msg)
{
	message = msg;
	return (*this);
}

Message &Message::SetData(void *_data)
{
	data = _data;
	return (*this);
}

Message &Message::operator=(const Message &other)
{
	sender = other.sender;
	receiver = other.receiver;
	message = other.message;
	data = other.data;
	return (*this);
}
