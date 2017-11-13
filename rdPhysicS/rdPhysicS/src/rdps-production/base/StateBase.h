#ifndef	__STATE_BASE_H__
#define	__STATE_BASE_H__

#include "State.h"

RDPS_BEGIN
	PDCT_BEGIN
		class Collaborator;

		class StateBase : public State<Collaborator>
		{
		public:
			virtual ~StateBase() {};

			virtual void Enter(const Collaborator &c) {}
			virtual void Execute(const Collaborator &c) {};
			virtual void Esit(const Collaborator &c) {};
		};

	PDCT_END
RDPS_END

#endif//__STATE_BASE_H__