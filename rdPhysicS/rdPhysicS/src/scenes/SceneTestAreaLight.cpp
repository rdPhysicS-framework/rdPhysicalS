#include "SceneTestAreaLight.h"
#include "..\World.h"
#include "..\system\Keyboard.h"
#include "..\rdps-frwk\lights\AmbientOccluder.h"
#include <SDL.h>

using namespace rdps;

SceneTestAreaLight::SceneTestAreaLight() :
					SceneBase()
{
	SetAmbient(new AmbientOccluder(
				RT::Vec3f(1.0f, 1.0f, 1.0f),
				1.5f, 0.25f));
}

SceneTestAreaLight::~SceneTestAreaLight()
{}

void SceneTestAreaLight::Init()
{
	World::Quality(MEDIUM);
	World::World::EnableAreaLight();

	GetCamera()->Configure(RT::Vec3f(-702.0f, -108.0f, -270.0f),
						   RT::Vec3f(-540.0f, -100.0f, 0.0f),
						   RT::Vec3f(0.0f, 1.0f, 0.0f),
						   800.0f, 1.5f);
	/*Adiciona as luzes*/
	/*CreateAreaLight(new Rectangle(RT::Vec3f(864, 756, -216),
								  RT::Vec3f(216, 0, 0),
								  RT::Vec3f(0, 0, 216),
								  RT::Vec3f(0, -1, 0),
								  new EmissiveMaterial(WHITE, 50.0f)));

	CreateAreaLight(new Rectangle(RT::Vec3f(864, 756, 1296),
								  RT::Vec3f(216, 0, 0),
								  RT::Vec3f(0, 0, 216),
								  RT::Vec3f(0, -1, 0),
								  new EmissiveMaterial(WHITE, 50.0f)));

	CreateAreaLight(new Rectangle(RT::Vec3f(-1296, 756, -216),
								  RT::Vec3f(216, 0, 0),
								  RT::Vec3f(0, 0, 216),
								  RT::Vec3f(0, -1, 0),
								  new EmissiveMaterial(WHITE, 50.0f)));
	
	CreateAreaLight(new Rectangle(RT::Vec3f(864, 756, -216),
								  RT::Vec3f(216, 0, 0),
								  RT::Vec3f(0, 0, 216),
								  RT::Vec3f(0, -1, 0),
								  new EmissiveMaterial(WHITE, 50.0f)));*/

	/*CreateAreaLight(new Disk(RT::Vec3f(972, 756.0f, -108.0f),
							  RT::Vec3f(0.0f, -1.0f, 0.0f), 
							  300.0f, new EmissiveMaterial(WHITE, 10.0f)));

	CreateAreaLight(new Disk(RT::Vec3f(864.0f, 756.0f, 1296.0f),
							  RT::Vec3f(0.0f, -1.0f, 0.0f), 
							  300.0f, new EmissiveMaterial(WHITE, 10.0f)));

	CreateAreaLight(new Disk(RT::Vec3f(-1188.0f, 756.0f, -108.0f),
							  RT::Vec3f(0.0f, -1.0f, 0.0f), 
							  300.0f, new EmissiveMaterial(WHITE, 10.0f)));

	CreateAreaLight(new Disk(RT::Vec3f(-1188.0f, 756.0f, 1404.0f),
							  RT::Vec3f(0.0f, -1.0f, 0.0f), 
							  300.0f, new EmissiveMaterial(WHITE, 10.0f)));*/

	CreateAreaLight(new SphericalLamp(RT::Vec3f(972, 756.0f, -108.0f),
		100.0f, new EmissiveMaterial(WHITE, 20.0f)));

	CreateAreaLight(new SphericalLamp(RT::Vec3f(864.0f, 756.0f, 1296.0f),
		100.0f, new EmissiveMaterial(WHITE, 20.0f)));

	CreateAreaLight(new SphericalLamp(RT::Vec3f(-1188.0f, 756.0f, -108.0f),
		100.0f, new EmissiveMaterial(WHITE, 20.0f)));

	CreateAreaLight(new SphericalLamp(RT::Vec3f(-1188.0f, 756.0f, 1404.0f),
		100.0f, new EmissiveMaterial(WHITE, 20.0f)));


	/*Adiciona os planos*/
	CreatePlane(RT::Vec3f(0.0f, -324.0f, 0.0f),
				RT::Vec3f(0.0f, 1.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f),
					0.2f, 0.7f, 0.5f, 25.0f));

	CreatePlane(RT::Vec3f(0.0f, 0.0f, 2419.0f),
				RT::Vec3f(0.0f, 0.0f, -1.0f),
				new PhongMaterial(RT::Vec3f(0.6f, 0.5f, 0.5f),
								  0.2f, 1.0f, 0.8f, 25.0f));

	CreatePlane(RT::Vec3f(-1296.0f, 0.0f, 0.0f),
				RT::Vec3f(1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.5f, 0.6f),
								  0.2f, 1.0f, 0.8f, 25.0f));

	CreatePlane(RT::Vec3f(1296.0f, 0.0f, 0.0f),
				RT::Vec3f(-1.0f, 0.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.5f, 0.5f, 0.6f),
								  0.2f, 1.0f, 0.8f, 25.0f));

	CreatePlane(RT::Vec3f(0.0f, 820.0f, 0.0f),
				RT::Vec3f(0.0f, -1.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
								  0.2f, 0.7f, 0.5f, 1.0f));

	/*Adiciona as esferas*/
	CreateSphere(RT::Vec3f(162.0f, 54.0f, 432.0f), 216.0f,
		new ReflectiveMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
						  0.2f, 0.7f, 0.8f, 1.0f, 0.2f));
	

	float shininess = 0.4f * 128.0f;

	/*CreateSphere(RT::Vec3f(162.0f, 54.0f, 432.0f), 216.0f,
		new PhongMaterial(new BRDF(RT::Vec3f(0.24725f, 0.1995f, 0.0745f), 1.0f),
			new BRDF(RT::Vec3f(0.75164f, 0.60648f, 0.22648f), 1.0f, DIFFUSE),
			new GlossySpecular(RT::Vec3f(0.628281f, 0.555802f, 0.366065f), 1.0f, shininess)));*/

	/*CreateSphere(RT::Vec3f(162.0f, 54.0f, 432.0f), 216.0f,
				 new PhongMaterial(new BRDF(RT::Vec3f(0.0215f, 0.1745f, 0.0215f), 1.0f),
								   new BRDF(RT::Vec3f(0.07568f, 0.61424f, 0.07568f), 1.0f, DIFFUSE),
								   new GlossySpecular(RT::Vec3f(0.633f, 0.727811f, 0.633f), 1.0f, shininess)));*/

	CreateSphere(RT::Vec3f(-540.0f, -86.0f, 432.0f), 270.0f,
		new ReflectiveMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
								0.2f, 0.7f, 0.8f, 1.0f, 0.4f));

	/*Adiciona o Cubo*/
	CreateCube(RT::Vec3f(0.0f, -324.0f, 270.0f),
			   RT::Vec3f(324.0f, 162.0f, 324.0f),
			   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
			   	                 0.2f, 0.7f, 0.2f, 1.0f));
}

void SceneTestAreaLight::Update(const float secs)
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
