#include "SceneBase.h"
#include "..\camera\Camera.h"

USING_RDPS
USING_FRWK

SceneBase::SceneBase() :
	renderer(nullptr),
	camera(new Camera(RT::Vec3f(0.0f, 0.0f, -300.0f), 
					  RT::Vec3f(0.0f, 0.0f, 0.0f), 
					  RT::Vec3f(0.0f, 1.0f, 0.0f), 
					  800.0f))
{}

SceneBase::~SceneBase()
{
	if (renderer)
		delete renderer;
	if (camera)
		delete camera;
}

void SceneBase::Draw()
{
	camera->Render(*this);
}
