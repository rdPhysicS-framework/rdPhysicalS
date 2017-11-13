#ifndef	__PACKER_OBJECTS_H__
#define	__PACKER_OBJECTS_H__

#include "..\base\Collaborator.h"

RDPS_BEGIN
	PDCT_BEGIN
		class ManagerObjects;
		class ObjectsHostPkg;
		class Container;

		class PackerObjects : public Collaborator
		{
		private:
			const ObjectsHostPkg *package;
			Container *container;

		public:
			PackerObjects(Container *_container);
			PackerObjects(const PackerObjects &other);
			~PackerObjects();

			//PackerObjects &SetPackage(const ObjectsHostPkg *_package);
			//PackerObjects &SetConatiner(Container *_container);

			virtual PackerObjects *Clone();
			virtual PackerObjects &Init();
			virtual PackerObjects &ExecuteFunction();
			virtual PackerObjects &Exit();
			virtual bool HandleMessage(const Message &message);
		};
	PDCT_END
RDPS_END

#endif//__PACKER_OBJECTS_H__