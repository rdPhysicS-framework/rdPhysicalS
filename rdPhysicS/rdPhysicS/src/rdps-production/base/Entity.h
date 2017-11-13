#ifndef	__ENTITY_H__
#define	__ENTITY_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Message;

		class Entity
		{
		public:
			virtual ~Entity() {}
			virtual Entity &Init() = 0;
			virtual Entity &ExecuteFunction() = 0;
			virtual Entity &Exit() = 0;
			virtual bool HandleMessage(const Message &message) = 0;
		};

	PDCT_END
RDPS_END

#endif//__ENTITY_H__