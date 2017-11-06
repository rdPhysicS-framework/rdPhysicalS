#ifndef	__GEOMETRIC_OBJECT_H__
#define	__GEOMETRIC_OBJECT_H__

#include "..\..\GlobalDefs.h"
#include "Actor.h"
#include "ObjectBase.h"

RDPS_BEGIN
	FRWK_BEGIN

		class GeometricObject : public ObjectBase, Actor
		{
		private:
			Material *material;

		public:
			GeometricObject(Material *_material, 
							const TypeObject type);
			/*GeometricObject(Material *_material,
							const TypeObject type,
							const RT::Vec3f &position,
							const RT::Vec3f &rotation,
							const RT::Vec3f &scale);*/
			GeometricObject(const GeometricObject &other);
			virtual ~GeometricObject();

			virtual GeometricObject *Clone() const = 0;

			GeometricObject &operator=(const GeometricObject &other);
			virtual inline Material *GetMaterial() const { return material; }
			virtual GeometricObject &SetMaterial(const Material &_material);
		};
		
	FRWK_END
RDPS_END

#endif//__GEOMETRIC_OBJECT_H__