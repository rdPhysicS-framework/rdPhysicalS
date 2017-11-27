#include "Test.h"

USING_RDPS

Test::Test() :
	SceneBase()
{
	Init();
}

Test::~Test()
{
}

void Test::Init()
{
	GetCamera()->Configure(RT::Vec3f(-702.0f, -108.0f, -270.0f), 
						   RT::Vec3f(-540.0f, -100.0f, 0.0f), 
						   RT::Vec3f(0.0f, 1.0f, 0.0f), 
						   800.0f, 1.5f);

	/*Adiciona as luzes*/
	CreatePointLight(RT::Vec3f(972, 756.0f, -108.0f), WHITE, 1.0f);
	CreatePointLight(RT::Vec3f(972.0f, 756.0f, 1404.0f), WHITE, 1.0f);
	CreatePointLight(RT::Vec3f(-1188.0f, 756.0f, -108.0f), WHITE, 1.0f);
	CreatePointLight(RT::Vec3f(-1188.0f, 756.0f, 1404.0f), WHITE, 1.0f);

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

	/*Adiciona as esferas*/
	CreateSphere(RT::Vec3f(162.0f, 54.0f, 432.0f), 216.0f,
				 new PhongMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
								   0.2f, 0.7f, 0.8f, 1.0f));

	id = CreateSphere(RT::Vec3f(-540.0f, -86.0f, 432.0f), 270.0f,
					  new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 0.7f),
										0.2f, 0.7f, 0.8f, 1.0f));

	/*Adiciona o Cubo*/
	CreateCube(RT::Vec3f(0.0f, -324.0f, 270.0f), 
			   RT::Vec3f(324.0f, 162.0f, 324.0f),
			   new PhongMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
								 0.2f, 0.7f, 0.2f, 1.0f));
}

void Test::Update(const float secs)
{
	//GetObject(id)->GetTransform()->Translate(10.0f, -200.0f, 400.0f);
}
