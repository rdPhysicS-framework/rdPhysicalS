#ifndef	__TO_PACK_OBJECTS_FOR_DEVICE_H__
#define	__TO_PACK_OBJECTS_FOR_DEVICE_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	PDCT_BEGIN

		class PackerObjects;

		class ToPackObjectsForDevice : public State<PackerObjects>
		{
		private:
			static State<PackerObjects> *INSTANCE;

		private:
			ToPackObjectsForDevice();

		public:
			~ToPackObjectsForDevice();

			static State<PackerObjects> *Get();

			virtual void Enter(const PackerObjects &c);
			virtual void Execute(const PackerObjects &c);
			virtual void Exit(const PackerObjects &c);
			virtual bool OnMessage(const PackerObjects &c, const Message &msg);
		};

	PDCT_END
RDPS_END

#endif//__TO_PACK_OBJECTS_FOR_DEVICE_H__