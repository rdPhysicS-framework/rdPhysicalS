#ifndef	__STATE_H__
#define	__STATE_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Message;

		template<class T>
		class State
		{
		public:
			virtual ~State() {}
			virtual void Enter(const T &c) = 0;
			virtual void Execute(const T &c) = 0;
			virtual void Exit(const T &c) = 0;
			virtual bool OnMessage(const T &c, const Message &msg) = 0;
		};

	PDCT_END
RDPS_END

#endif//__STATE_H__