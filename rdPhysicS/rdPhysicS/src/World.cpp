#include "World.h"
#include "rdps-CL\Application\ApplicationCL.h"

USING_RDPS
USING_CL

World *World::instance = nullptr;

World::World(ApplicationCL *_app) :
	   app(_app)
{}

World::~World()
{
	if (app) 
		delete app;
}

void World::Set(ApplicationCL *_app)
{

	if (!app)
		app = _app;

}

World *World::Get()
{
	if (!instance)
		instance = new World();

	return instance;
}

ApplicationCL *World::GetApp() const
{
	return app;
}
