#ifndef	__OBJECT_DISPATCHER_H__
#define	__OBJECT_DISPATCHER_H__

#include "..\base\Collaborator.h"

RDPS_BEGIN
	
	PKG_BEGIN class Container; PKG_END

	PDCT_BEGIN

		class ObjectDispatcher : public Collaborator
		{
		private:
			PKG Container *container;

		public:
			ObjectDispatcher(PKG Container *_container);
			ObjectDispatcher(const ObjectDispatcher &other);
			~ObjectDispatcher();

			PKG Container *GetContainer() const;

			virtual Collaborator *Clone();
			virtual Collaborator &Init();
			virtual Collaborator &ExecuteFunction();
			virtual Collaborator &Exit();
		};

	PDCT_END
RDPS_END

#endif//__OBJECT_DISPATCHER_H__