#ifndef	__SCENE_BASE_H__
#define	__SCENE_BASE_H__

#include "..\..\GlobalDefs.h"
#include <RTmath.h>

RDPS_BEGIN

	PKG_BEGIN  class Renderer; PKG_END;

	FRWK_BEGIN
		
		class Camera;
		class GeometricObject;
		class Light;
		class AmbientLight;
		class Material;

		class SceneBase
		{
		private:
			Camera *camera;
			Light *ambient;

		private:
			size_t AddObject(GeometricObject *obj);
			size_t AddLight(Light *light);

		protected:

			int CreateCube(const RT::Vec3f &initPoint, 
						   const RT::Vec3f &size, 
						   Material *material);
			int CreatePlane(const RT::Vec3f &point,
							const RT::Vec3f &normal,
							Material *material);
			int CreateSphere(const RT::Vec3f &center,
							 const float radius,
							 Material *material);

			int CreatePointLight(const RT::Vec3f &point, 
								 const RT::Vec3f &color, 
								 const float exp);

			GeometricObject *GetObject(const size_t id) const;
			Light *GetLight(const size_t id) const;
		public:
			SceneBase();
			virtual ~SceneBase();

			PKG Renderer *GetRenderer() const;
			Camera *GetCamera() const;
			Light *GetAmbientLight() const;

			virtual void Init() = 0;
			virtual void Update(const float secs) = 0;
			virtual void Draw();
		};

	FRWK_END
RDPS_END

#endif//__SCENE_BASE_H__