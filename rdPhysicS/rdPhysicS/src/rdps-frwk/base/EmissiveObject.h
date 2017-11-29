#ifndef	__EMISSIVE_OBJECT_H__
#define	__EMISSIVE_OBJECT_H__

#include "ObjectBase.h"

RDPS_BEGIN
	FRWK_BEGIN

		class EmissiveObject : public ObjectBase
		{
		private:
			Material *material;
			TypeObjectEmissive typeOE;

		public:
			EmissiveObject(const TypeObjectEmissive _typeOE,
						   Material *_material = nullptr);
			EmissiveObject(const EmissiveObject &other);
			virtual ~EmissiveObject();

			virtual ObjectBase *Clone() const = 0;
			EmissiveObject &operator=(const EmissiveObject &other);
			virtual Material *GetMaterial() const;
			virtual EmissiveObject &SetMaterial(const Material &_material);
		};

	FRWK_END
RDPS_END

#endif//__EMISSIVE_OBJECT_H__