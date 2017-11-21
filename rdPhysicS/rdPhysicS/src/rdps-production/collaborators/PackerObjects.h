#ifndef	__PACKER_OBJECTS_H__
#define	__PACKER_OBJECTS_H__

#include "..\base\Collaborator.h"

RDPS_BEGIN
		PKG_BEGIN class Container; PKG_END
	PDCT_BEGIN
		class ManagerObjects;
		class ObjectsHostPkg;

		class PackerObjects : public Collaborator
		{
		private:
			const ObjectsHostPkg *package;
			PKG Container *container;

		public:
			PackerObjects(PKG Container *_container);
			PackerObjects(const PackerObjects &other);
			~PackerObjects();

			const ObjectsHostPkg *GetPackage() const;
			PKG Container *GetContainer() const;
			PackerObjects &SetPackage(const ObjectsHostPkg *_package);
			PackerObjects &SetContainer(PKG Container *_container);

			virtual PackerObjects *Clone();
			virtual PackerObjects &Init();
			virtual PackerObjects &ExecuteFunction();
			virtual PackerObjects &Exit();
		};
	PDCT_END
RDPS_END

#endif//__PACKER_OBJECTS_H__