#ifndef	__SCENE_BASE_H__
#define	__SCENE_BASE_H__

#include "..\..\GlobalDefs.h"

RDPS_BEGIN

	PKG_BEGIN  class Renderer; PKG_END;

	FRWK_BEGIN
		
		class Camera;

		class SceneBase
		{
		protected:
			PKG Renderer *renderer;
			Camera *camera;

		public:
			SceneBase();
			virtual ~SceneBase();

			inline PKG Renderer *GetRenderer() const { return renderer; }
			inline Camera	*GetCamera()   const { return camera;   }

			virtual void Init() = 0;
			virtual void Update(const float secs) = 0;
			virtual void Draw();
		};

	FRWK_END
RDPS_END

#endif//__SCENE_BASE_H__