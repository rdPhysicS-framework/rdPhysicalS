#ifndef	__WORLD_H__
#define	__WORLD_H__

#include "GlobalDefs.h"

RDPS_BEGIN
	CL_BEGIN class ApplicationCL; CL_END;

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