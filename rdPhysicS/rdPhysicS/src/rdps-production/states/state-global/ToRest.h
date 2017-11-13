#ifndef	__TO_REST_H__
#define	__TO_REST_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Collaborator;

		class ToRest : public State<Collaborator>
		{
		private:
			static State<Collaborator> *INSTANCE;

		private:
			ToRest();

		public:
			~ToRest();

			static State<Collaborator> *Get();

			virtual void Enter(const Collaborator &c);
			virtual void Execute(const Collaborator &c);
			virtual void Exit(const Collaborator &c);
			virtual bool OnMessage(const Collaborator &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_REST_H__