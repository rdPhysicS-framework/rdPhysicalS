#ifndef	__TO_SEND_OBJECTS_FOR_PACK_H__
#define	__TO_SEND_OBJECTS_FOR_PACK_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class ObjectDispatcher;

		class ToSendObjectsForPack : public State<ObjectDispatcher>
		{
		private:
			static State<ObjectDispatcher> *INSTANCE;

		private:
			ToSendObjectsForPack();

		public:
			~ToSendObjectsForPack();

			static State<ObjectDispatcher> *Get();

			virtual void Enter(const ObjectDispatcher &c);
			virtual void Execute(const ObjectDispatcher &c);
			virtual void Exit(const ObjectDispatcher &c);
			virtual bool OnMessage(const ObjectDispatcher &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_SEND_OBJECTS_FOR_PACK_H__