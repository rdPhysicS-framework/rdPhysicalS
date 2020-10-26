#include "RealTime.h"
#include "..\rdps-frwk\includes_frwk.h"
#include "..\system\Keyboard.h"
#include <SDL.h>

USING_RDPS

RealTime::RealTime() :
	SceneBase()
{}

RealTime::~RealTime()
{}

void RealTime::Init()
{
	World::Quality(VERY_LOW);

	/*Configura camera*/
	GetCamera()->Configure(RT::Vec3f(0.0f, 0.0f, -270.0f),
						   RT::Vec3f(0.0f, 0.0f, 0.0f),
						   RT::Vec3f(0.0f, 1.0f, 0.0f),
						   400.0f, 1.0f);

	/*Adiciona a luz*/
	CreatePointLight(new SphericalLamp(RT::Vec3f(0.0f, 800.0f, 120.0f),
									   100.0f, new EmissiveMaterial(WHITE, 1.0f)),
									   RT::Vec3f(0.0f, 800.0f, 120.0f), WHITE, 5.0f);

	/*Adiciona o plano(chao)*/
	CreatePlane(RT::Vec3f(0.0f, -324.0f, 0.0f),
				RT::Vec3f(0.0f, 1.0f, 0.0f),
				new PhongMaterial(RT::Vec3f(0.4f, 0.3f, 0.3f),
								  0.2f, 0.7f, 0.5f, 1.0f));


	/*Adiciona as esferas*/
	id1 = CreateSphere(RT::Vec3f(), 100.0f,
					   new PhongMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
					   0.2f, 0.7f, 0.8f, 1.0f));

	Sphere *s = (Sphere*)GetObject(id1);
	/*move o objeto para o local desejado*/
	s->GetTransform()->Translate(120.0f, 0.0f, 0.0f);

	id2 = CreateSphere(RT::Vec3f(), 100.0f,
					   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
					   0.2f, 0.7f, 0.8f, 1.0f));

	s = (Sphere*)GetObject(id2);
	/*move o objeto para o local desejado*/
	s->GetTransform()->Translate(-120.0f, 0.0f, 0.0f);
}

void RealTime::Update(const float secs)
{
	Sphere *s = (Sphere*)GetObject(id1);
	/*faz as transformações geometricas*/
	s->GetTransform()->RotateY(15 * secs);

	s = (Sphere*)GetObject(id2);
	/*faz as transformações geometricas*/
	s->GetTransform()->RotateY(15 * secs);

	Camera *c = GetCamera();
	float x = c->GetLookAt().x;
	float y = c->GetLookAt().y;

	if (Keyboard::GetInstance()->IsDown(SDLK_a))
	{
		c->SetLookAt(RT::Vec3f(x - 100.0f * secs, c->GetLookAt().y, c->GetLookAt().z));
	}
	else if (Keyboard::GetInstance()->IsDown(SDLK_d))
	{
		c->SetLookAt(RT::Vec3f(x + 100.0f * secs, c->GetLookAt().y, c->GetLookAt().z));
	}
	else if (Keyboard::GetInstance()->IsDown(SDLK_w))
	{
		c->SetLookAt(RT::Vec3f(x, y + 100.0f * secs, c->GetLookAt().z));
	}
	else if (Keyboard::GetInstance()->IsDown(SDLK_s))
	{
		c->SetLookAt(RT::Vec3f(x, y - 100.0f * secs, c->GetLookAt().z));
	}
}

