#ifndef	__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__
#define	__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class ObjectDispatcher;

		class ToSendObjectsForTheDevice : public State<ObjectDispatcher>
		{
		private:
			static State<ObjectDispatcher> *INSTANCE;

		private:
			ToSendObjectsForTheDevice();

		public:
			~ToSendObjectsForTheDevice();

			static State<ObjectDispatcher> *Get();

			virtual void Enter(const ObjectDispatcher &c);
			virtual void Execute(const ObjectDispatcher &c);
			virtual void Exit(const ObjectDispatcher &c);
			virtual bool OnMessage(const ObjectDispatcher &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_SEND_OBJECTS_FOR_THE_DEVICE_H__