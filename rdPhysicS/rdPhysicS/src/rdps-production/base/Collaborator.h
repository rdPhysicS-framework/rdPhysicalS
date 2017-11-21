#ifndef	__COLLABORATOR_H__
#define	__COLLABORATOR_H__

#include "Entity.h"

RDPS_BEGIN
	PDCT_BEGIN

		class StateMachine;

		class Collaborator : public Entity
		{
		protected:
			CollaboratorsFunction function;
			StateMachine *stateMachine;

		public:
			Collaborator(const CollaboratorsFunction _function,
						 StateMachine *_stateMachine);
			Collaborator(const Collaborator &other);
			virtual ~Collaborator();

			const CollaboratorsFunction GetFunction() const;
			StateMachine *GetStateMachine() const;

			virtual Collaborator *Clone() = 0;
			virtual Collaborator &Init() = 0;
			virtual Collaborator &ExecuteFunction() = 0;
			virtual Collaborator &Exit() = 0;
			virtual bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__COLLABORATOR_H__