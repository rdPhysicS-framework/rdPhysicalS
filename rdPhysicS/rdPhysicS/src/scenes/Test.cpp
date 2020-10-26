#include "Test.h"
#include "..\rdps-frwk\includes_frwk.h"
#include "..\system\Keyboard.h"
#include <SDL.h>

USING_RDPS

Test::Test() :
	SceneBase()
{
	//();
}

Test::~Test()
{
}

void Test::Init()
{
	World::Quality(VERY_LOW);
	GetCamera()->Configure(RT::Vec3f(-702.0f, -108.0f, -270.0f), 
						   RT::Vec3f(-540.0f, -100.0f, 0.0f), 
						   RT::Vec3f(0.0f, 1.0f, 0.0f), 
						   800.0f, 1.5f);

	/*GetCamera()->Configure(RT::Vec3f(0.0f, 0.0f, -270.0f), 
						    RT::Vec3f(), 
						    RT::Vec3f(0.0f, 1.0f, 0.0f), 
						    400.0f, 1.0f);*/
	/*Adiciona as luzes*/

	/*CreatePointLight(new Rectangle(RT::Vec3f(864, 756, 1296), 
								  RT::Vec3f(216, 0, 0),
								   RT::Vec3f(0, 0, 216),
								   RT::Vec3f(0, -1, 0),
								   new EmissiveMaterial(WHITE, 50.0f)), 
					  RT::Vec3f(972.0f, 756.0f, 1404.0f), WHITE, 1.0f);*/

	/*CreatePointLight(new Disk(RT::Vec3f(864.0f, 756.0f, 1296.0f),
							  RT::Vec3f(0.0f, -1.0f, 0.0f), 
							  200.0f, new EmissiveMaterial(WHITE, 50.0f)),
					 RT::Vec3f(864.0f, 756.0f, 1296.0f), WHITE, 1.0f);

	CreatePointLight(new Rectangle(RT::Vec3f(-1296, 756, -216), 
								   RT::Vec3f(216, 0, 0),
								   RT::Vec3f(0, 0, 216),
								   RT::Vec3f(0, -1, 0),
								   new EmissiveMaterial(WHITE, 50.0f)),
					 RT::Vec3f(-1188.0f, 756.0f, -108.0f), WHITE, 1.0f);

	CreatePointLight(new Rectangle(RT::Vec3f(864, 756, -216), 
								   RT::Vec3f(216, 0, 0),
								   RT::Vec3f(0, 0, 216),
								   RT::Vec3f(0, -1, 0),
								   new EmissiveMaterial(WHITE, 50.0f)),
					 RT::Vec3f(-1188.0f, 756.0f, 1404.0f), WHITE, 1.0f);*/


	CreatePointLight(new SphericalLamp(RT::Vec3f(972, 756.0f, -108.0f),
		100.0f, new EmissiveMaterial(WHITE, 1.0f)),
	RT::Vec3f(972.0f, 756.0f, 1404.0f), WHITE, 1.0f);

	CreatePointLight(new SphericalLamp(RT::Vec3f(864.0f, 756.0f, 1296.0f),
		100.0f, new EmissiveMaterial(WHITE, 1.0f)),
					 RT::Vec3f(864.0f, 756.0f, 1296.0f), WHITE, 1.0f);

	CreatePointLight(new SphericalLamp(RT::Vec3f(-1188.0f, 756.0f, -108.0f),
		100.0f, new EmissiveMaterial(WHITE, 1.0f)),
		RT::Vec3f(-1188.0f, 756.0f, -108.0f), WHITE, 1.0f);

	CreatePointLight(new SphericalLamp(RT::Vec3f(-1188.0f, 756.0f, 1404.0f),
		100.0f, new EmissiveMaterial(WHITE, 1.0f)),
		RT::Vec3f(-1188.0f, 756.0f, 1404.0f), WHITE, 1.0f);


	/*Adiciona os planos*/
	CreatePlane(RT::Vec3f(0.0f, -324.0f, 0.0f), 
				RT::Vec3f(0.0f, 1.0f, 0.0f), 
				new PhongMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f), 
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(0.0f, 0.0f, 2419.0f),
				RT::Vec3f(0.0f, 0.0f, -1.0f),
			    new PhongMaterial(RT::Vec3f(0.6f, 0.5f, 0.5f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(-1296.0f, 0.0f, 0.0f),
				RT::Vec3f(1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.6f, 0.6f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(1296.0f, 0.0f, 0.0f),
				RT::Vec3f(-1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.6f, 0.6f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	CreatePlane(RT::Vec3f(0.0f, 800.0f, 0.0f),
				RT::Vec3f(0.0f, -1.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	/*id1 = CreateSphere(RT::Vec3f(), 216.0f,
		new PhongMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
			0.2f, 0.7f, 0.8f, 1.0f));*/

	id1 = CreateSphere(RT::Vec3f(), 216.0f,
		new ReflectiveMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
								0.2f, 0.7f, 0.8f, 1.0f, 0.1f));

	Sphere *s = (Sphere*)GetObject(id1);
	s->GetTransform()->Translate(162.0f, 54.0f, 432.0f);

	id2 = CreateSphere(RT::Vec3f(), 270.0f,
		new ReflectiveMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
			0.2f, 0.7f, 0.8f, 1.0f, 0.1f));

	s = (Sphere*)GetObject(id2);
	s->GetTransform()->Translate(-540.0f, -86.0f, 432.0f);

	/*Adiciona o Cubo*/
	CreateCube(RT::Vec3f(0.0f, -324.0f, 270.0f), 
			   RT::Vec3f(324.0f, 162.0f, 324.0f),
			   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
								 0.2f, 0.7f, 0.2f, 1.0f));
}

void Test::Update(const float secs)
{
	Camera *c = GetCamera();
	float x = c->GetLookAt().x;

	if (Keyboard::GetInstance()->IsDown(SDLK_a))
	{
		c->SetLookAt(RT::Vec3f(x - 100.0f * secs, c->GetLookAt().y, c->GetLookAt().z));
	}
	else if (Keyboard::GetInstance()->IsDown(SDLK_d))
	{
		c->SetLookAt(RT::Vec3f(x + 100.0f * secs, c->GetLookAt().y, c->GetLookAt().z));
	}
}
