#include "World.h"

USING_RDPS
USING_CL

World *World::instance = new World();

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
	return instance;
}

ApplicationCL *World::GetApp() const
{
	return app;
}
