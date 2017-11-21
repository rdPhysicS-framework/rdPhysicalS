#ifndef	__MANAGER_OBJECTS_H__
#define	__MANAGER_OBJECTS_H__

#include "..\base\Collaborator.h"
#include "..\Util\ObjectsHostPkg.h"

RDPS_BEGIN

	PDCT_BEGIN

		class ManagerObjects : public Collaborator
		{
		private:
			ObjectsHostPkg *package;

		public:
			ManagerObjects();
			ManagerObjects(const ManagerObjects &other);
			~ManagerObjects();

			const ObjectsHostPkg *GetPackage() const;

			const int AddObject(FRWK GeometricObject *object);
			ManagerObjects &RemoveObject(const int id);
			const int AddLight(FRWK Light *light);
			ManagerObjects &RemoveLight(const int id);
			ManagerObjects &SetViewPlane(FRWK ViewPlane *vp);
			ManagerObjects &SetCamera(FRWK Camera *camera);

			virtual ManagerObjects *Clone();
			virtual ManagerObjects &Init();
			virtual ManagerObjects &ExecuteFunction();
			virtual ManagerObjects &Exit();
		};

	PDCT_END
RDPS_END

#endif//__MANAGER_OBJECTS_H__