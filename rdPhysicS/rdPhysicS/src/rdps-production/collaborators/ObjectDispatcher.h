#ifndef	__OBJECT_DISPATCHER_H__
#define	__OBJECT_DISPATCHER_H__

#include "..\base\Collaborator.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Container;

		class ObjectDispatcher : public Collaborator
		{
		private:
			Container *container;

		public:
			ObjectDispatcher();
			ObjectDispatcher(const ObjectDispatcher &other);
			~ObjectDispatcher();

			virtual Collaborator *Clone();
			virtual Collaborator &Init();
			virtual Collaborator &ExecuteFunction();
			virtual Collaborator &Exit();
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__OBJECT_DISPATCHER_H__