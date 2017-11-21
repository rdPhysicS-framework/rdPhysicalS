#ifndef	__TO_PROCESS_OBJECT_TO_PACK_H__
#define	__TO_PROCESS_OBJECT_TO_PACK_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class ManagerObjects;

		class ToProcessObjectsToPack : public State<ManagerObjects>
		{
		private:
			static State<ManagerObjects> *INSTANCE;

		private:
			ToProcessObjectsToPack();

		public:
			~ToProcessObjectsToPack();

			static State<ManagerObjects> *Get();

			virtual void Enter(const ManagerObjects &c);
			virtual void Execute(const ManagerObjects &c);
			virtual void Exit(const ManagerObjects &c);
			virtual bool OnMessage(const ManagerObjects &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_PROCESS_OBJECT_TO_PACK_H__