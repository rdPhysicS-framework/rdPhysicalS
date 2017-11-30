#ifndef	__WORLD_H__
#define	__WORLD_H__

#include "GlobalDefs.h"
#include "rdps-CL\Application\ApplicationCL.h"

RDPS_BEGIN

	PKG_BEGIN 
		class Container;
		class Renderer;
	PKG_END
	PDCT_BEGIN 
		class ManagerObjects;
		class ObjectDispatcher;
		class PackerObjects;
	PDCT_END;
	FRWK_BEGIN class Sampler; FRWK_END

	class World
	{
	private:
		static CL ApplicationCL *app;
		static PKG Container *container;
		static PDCT ManagerObjects *manager;
		static PDCT ObjectDispatcher *oDispatcher;
		static PDCT PackerObjects *packer;
		static PKG Renderer *renderer;
		static FRWK Sampler *sampler;
		static byte flags;

	public:
		World();
		~World();

		static PKG Renderer *GetRenderer();
		static PKG Container *GetContainer();
		static PDCT ManagerObjects *GetManager();
		static PDCT ObjectDispatcher *GetObjectDispatcher();
		static PDCT PackerObjects *GetPackerObjects();
		static byte GetFlags();

		static void SetApp(CL ApplicationCL *_app);
		static void SetViewPlane(const int w, const int h);
		static void Quality(const int r);
		static void Enable(const byte _flags);
		static void EnableAreaLight();
		static void DisableAreaLight();

		static void Init();
		static void Update();
		static void Draw();

		static CL ApplicationCL *GetApp();
	};

RDPS_END

#endif//__WORLD_H__