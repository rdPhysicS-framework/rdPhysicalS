#ifndef	__TO_PACK_OBJECTS_FOR_DEVICE_H__
#define	__TO_PACK_OBJECTS_FOR_DEVICE_H__

#include "..\..\base\State.h"

RDPS_BEGIN
	
	FRWK_BEGIN
		class Light;
		class GeometricObject;
		class Camera;
		class ViewPlane;
		class Material;
	FRWK_END

	PKG_BEGIN 
		class Container; 
		struct RT_Material;
	PKG_END

	PDCT_BEGIN

		class PackerObjects;

		class ToPackObjectsForDevice : public State<PackerObjects>
		{
		private:
			static State<PackerObjects> *INSTANCE;

		private:
			ToPackObjectsForDevice();

			void ToPackLightData(const FRWK Light *light, 
								 const PackerObjects &c);

			void ToPackObjectData(const FRWK GeometricObject *object,
								  const PackerObjects &c);

			PKG RT_Material ToPackMaterialData(const FRWK Material *object);

			void ToPackCameraData(const FRWK Camera *object,
								  const PackerObjects &c);

			void ToPackWordData(const PackerObjects &c);

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