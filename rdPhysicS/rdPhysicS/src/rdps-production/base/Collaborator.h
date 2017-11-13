#ifndef	__COLLABORATOR_H__
#define	__COLLABORATOR_H__

#include "Entity.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Collaborator : public Entity
		{
		private:
			CollaboratorsFunction function;

		public:
			Collaborator(const CollaboratorsFunction _function);
			Collaborator(const Collaborator &other);
			virtual ~Collaborator() {}

			virtual Collaborator *Clone() = 0;
			virtual Collaborator &Init() = 0;
			virtual Collaborator &ExecuteFunction() = 0;
			virtual Collaborator &Exit() = 0;
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__COLLABORATOR_H__