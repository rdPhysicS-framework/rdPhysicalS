#include "World.h"
#include "rdps-packages\input\Container.h"
#include "rdps-packages\input\ContainerBuilder.h"
#include "rdps-packages\input\ContainerFactory.h"
#include "rdps-production\collaborators\ManagerObjects.h"
#include "rdps-production\collaborators\ObjectDispatcher.h"
#include "rdps-production\collaborators\PackerObjects.h"
#include "rdps-packages\object-CL\ObjectsPackage.h"
#include "rdps-packages\input\Package.h"
#include "rdps-CL\Application\ApplicationCL.h"
#include "rdps-CL\Application\ApplicationCLFactor.h"
#include "rdps-packages\output\Renderer.h"
#include "rdps-frwk\Util\ViewPlane.h"
#include "rdps-production\msg\Message.h"
#include "rdps-production\msg\MessageDispatcher.h"
#include "rdps-production\collaborators\GeneralManager.h"

USING_RDPS
USING_CL
USING_PKG
USING_FRWK
USING_PDCT

ApplicationCL *World::app = nullptr;
Container *World::container = nullptr;
ManagerObjects *World::manager = nullptr;
ObjectDispatcher *World::oDispatcher = nullptr;
PackerObjects *World::packer = nullptr;
Renderer *World::renderer = nullptr;

World::World()
{}

World::~World()
{
	if (app) 
		delete app;
	if (container)
		delete container;
	if(manager)
		delete manager;
	if(oDispatcher)
		delete oDispatcher;
	if(packer)
		delete packer;
	if(renderer)
		delete renderer;
}

PKG Renderer *World::GetRenderer()
{
	return renderer;
}

PKG Container *World::GetContainer()
{
	return container;
}

PDCT ManagerObjects *World::GetManager()
{
	return manager;
}

PDCT ObjectDispatcher *World::GetObjectDispatcher()
{
	return oDispatcher;
}

PDCT PackerObjects *World::GetPackerObjects()
{
	return packer;
}

void World::SetApp(ApplicationCL *_app)
{
	if (!app)
		app = _app;

}

void World::SetViewPlane(const int w, const int h)
{
	manager->SetViewPlane(new ViewPlane(w, h));
	renderer = new Renderer(w, h);
}

void World::Init()
{
	app = ApplicationCLFactor::CreateApplicationUsersInput();
	container = ContainerFactory::CreateContainer({ "world", "camera",
												    "lights", "objects" },
												    { new Package<RT_DataScene>(),
												      new Package<RT_Camera>(),
												      new Package<RT_Light>() ,
												      new Package<RT_Primitive>() });
	manager = new ManagerObjects();
	oDispatcher = new ObjectDispatcher(container);
	packer = new PackerObjects(container);
	packer->SetPackage(manager->GetPackage());

	GeneralManager::Get()->AddCollaborator(MANAGER_OF_OBJECTS, manager);
	GeneralManager::Get()->AddCollaborator(DELIVERER_OF_OBJECTS, oDispatcher);
	GeneralManager::Get()->AddCollaborator(PACKER_OF_OBJECTS, packer);
}

void World::Update()
{
	MessageDispatcher::DispatchMessage(nullptr, GeneralManager::Get(), "request");
	manager->ExecuteFunction();
	packer->ExecuteFunction();
	oDispatcher->ExecuteFunction();
}

void World::Draw()
{
	Update();
	World::GetApp()->Process(true);
}

ApplicationCL *World::GetApp()
{
	return app;
}
