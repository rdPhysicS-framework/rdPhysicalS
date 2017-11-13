#ifndef	__OBJECTS_HOST_PKG_H__
#define	__OBJECTS_HOST_PKG_H__

#include "..\..\GlobalDefs.h"
#include <vector>

RDPS_BEGIN
	FRWK_BEGIN
		class GeometricObject;
		class Light;
		class ViewPlane;
		class Camera;
	FRWK_END

	PDCT_BEGIN

		class ObjectsHostPkg
		{
		private:
			std::vector<FRWK GeometricObject*> objects;
			std::vector<FRWK Light*> lights;
			FRWK ViewPlane *vp;
			FRWK Camera *camera;

		public:
			ObjectsHostPkg();
			~ObjectsHostPkg();

			inline const std::vector<FRWK GeometricObject*> &GetObjects() const { return objects; }
			inline const std::vector<FRWK Light*> &GetLights() const { return lights; }

			const int AddObject(FRWK GeometricObject *object);
			ObjectsHostPkg &RemoveObject(const int id);
			const int AddLight(FRWK Light *light);
			ObjectsHostPkg &RemoveLight(const int id);
			ObjectsHostPkg &SetViewPlane(FRWK ViewPlane *vp);
			ObjectsHostPkg &SetCamera(FRWK Camera *camera);
		};

	PDCT_END
RDPS_END

#endif//__OBJECTS_HOST_PKG_H__