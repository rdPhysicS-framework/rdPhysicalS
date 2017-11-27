#ifndef	__ENTITY_H__
#define	__ENTITY_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN
	PDCT_BEGIN

		class Message;

		/********************************************************************************************************************************************
		 *
		 * Classe Base para todas as etidades existentes na aplicação que fazem trocas de mensagens.
		 * Todas as entidades devem herdar desta classe e sobreescrever os métodos.
		 *
		 ********************************************************************************************************************************************/
		class Entity
		{
		public:
			virtual ~Entity() {}
			virtual Entity &ExecuteFunction() = 0;
			virtual bool HandleMessage(const Message &message) = 0;
		};

	PDCT_END
RDPS_END

#endif//__ENTITY_H__