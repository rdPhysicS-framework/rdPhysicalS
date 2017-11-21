#ifndef	__STATE_MACHINE_H__
#define	__STATE_MACHINE_H__

#include "..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Collaborator;

		class StateMachine
		{
		private:
			Collaborator *myOwner;
			State<Collaborator> *currentState;
			State<Collaborator> *previousState;
			State<Collaborator> *globalState;

		public:
			StateMachine(Collaborator *owner);
			StateMachine(const StateMachine &other);
			~StateMachine();

			StateMachine *Clone() const;

			StateMachine &operator=(const StateMachine &other);

			Collaborator *GetOwner() const;
			State<Collaborator> *GetCurrentState()  const;
			State<Collaborator> *GetPreviousState() const;
			State<Collaborator> *GetGlobalState()   const;

			StateMachine &SetCurrentState(State<Collaborator> *_currentState);
			StateMachine &SetPreviousState(State<Collaborator> *_previousState);
			StateMachine &SetGlobalState(State<Collaborator> *_globalState);

			StateMachine &Update();
			StateMachine &ChangeState(State<Collaborator> *newState);
			StateMachine &ReverToPreviousState();
			bool HandleMessage(const Message &message);
		};

	PDCT_END
RDPS_END

#endif//__STATE_MACHINE_H__