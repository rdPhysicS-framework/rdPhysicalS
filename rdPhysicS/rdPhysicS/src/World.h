#ifndef	__WORLD_H__
#define	__WORLD_H__

#include "GlobalDefs.h"
#include "rdps-CL\Application\ApplicationCL.h"

RDPS_BEGIN

	class World
	{
	private:
		CL ApplicationCL *app;
		static World *instance;

	private:
		World(CL ApplicationCL *_app = nullptr);

	public:
		~World();
		static World *Get();
		void Set(CL ApplicationCL *_app);
		CL ApplicationCL *GetApp() const;
	};

RDPS_END

#endif//__WORLD_H__