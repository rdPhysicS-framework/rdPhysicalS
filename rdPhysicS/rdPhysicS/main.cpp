#include <iostream>
#include "src\Util\LogError.h"
#include "src\rdps-CL\Application\ApplicationCLFactor.h"
#include "src\rdps-CL\Application\ApplicationCL.h"
#include "src\rdps-packages\ArrayBuffer.h"
#include <SDL.h>
#include "src\rdps-CL\ClGlobalDef.h"
#include "src\rdps-packages\input\Package.h"
#include "src\rdps-packages\input\Container.h"
#include "src\rdps-packages\input\ContainerBuilder.h"
#include "src\rdps-packages\output\FinalProduct.h"
#include "src\rdps-packages\input\ContainerFactory.h"
#include "src\rdps-packages\object-CL\ObjectsPackage.h"
#include "src\World.h"
#include <SDL_image.h>

USING_RDPS
USING_CL
USING_PKG

int Save(const int *image, const int w, const int h)
{
	if (!image)
		return -1;

	SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	if (!img)
		Logger::Log("ERROR when saving the image");

	img->pixels = (cl_uint*)image;
	std::cout << "Digite um nome com a extencao(png) para a imagem: ";
	char infoname[128];
	std::cin >> infoname;
	std::string name = IMAGE_PATH;
	name += infoname;

	IMG_SavePNG(img, name.c_str());

	//SDL_FreeSurface(img);

	return 0;
}

void setObjects(RT_Primitive *objects)
{
	//RT::Mat4f m;

	objects[0].p = { 162, 54, 432 };
	objects[0].s = { 0, 0, 0 };
	objects[0].r = 216;
	objects[0].material = { { { 0.6f, 0.6f, 0.6f }, 0.2f, 0,    RT_LAMBERTIAN },
	{ { 0.6f, 0.6f, 0.6f }, 0.7f, 0,    RT_LAMBERTIAN },
	{ { 0.6f, 0.6f, 0.6f }, 0.8f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.6f, 0.6f, 0.6f }, 0.0f, 0,    RT_PERFECT_SPECULAR } };
	objects[0].type = RT_SPHERE;
	objects[0].bbox = { objects[0].p.x - (objects[0].r*objects[0].r + 4),
		objects[0].p.y - (objects[0].r*objects[0].r + 4),
		objects[0].p.z - (objects[0].r*objects[0].r + 4),
		objects[0].p.x + (objects[0].r*objects[0].r + 4),
		objects[0].p.y + (objects[0].r*objects[0].r + 4),
		objects[0].p.z + (objects[0].r*objects[0].r + 4) };
	
	//rdPhs::Transform *t = rdPhs::Transform::Get();
	/*t->CopyTransformMatrix(objects[0].invMatrix);
	t->Scale(1, 2.0f, 1)
	.RotateX(-90.0f)
	.Translate(162, 54, 432)
	.CopyTransformMatrix(objects[0].invMatrix);//.invMatrix[0]);*/
	/*m = RT::mt4::AffScaling(1, 1/2.0f, 1) *
	RT::mt4::AffRotationX(
	RT::Math::ToRadians(-90.0f))
	.Transpose() *
	RT::mt4::AffTranslation(-162, -54, -432);

	memcpy(objects[0].invMatrix, (void*)m.GetMatrix(), sizeof(objects[0].invMatrix));*/


	objects[1].p = { -540, -86, 432 };
	objects[1].s = { 0, 0, 0 };
	objects[1].r = 270;
	objects[1].material = { { { 0.7f, 0.7f, 1.0f }, 0.2f, 0,    RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 0.7f }, 0.7f, 0,    RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 0.7f }, 0.8f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.0f, 0.0f, 0.0f }, 0.0f, 0,    RT_PERFECT_SPECULAR } };
	objects[1].type = RT_SPHERE;
	//memcpy(objects[1].invMatrix, (void*)m.GetMatrix(), sizeof(objects[1].invMatrix));
	//t->CopyTransformMatrix(objects[1].invMatrix);
	objects[1].bbox = { objects[1].p.x - (objects[1].r*objects[1].r + 4),
		objects[1].p.y - (objects[1].r*objects[1].r + 4),
		objects[1].p.z - (objects[1].r*objects[1].r + 4),
		objects[1].p.x + (objects[1].r*objects[1].r + 4),
		objects[1].p.y + (objects[1].r*objects[1].r + 4),
		objects[1].p.z + (objects[1].r*objects[1].r + 4) };

	objects[2].p = { 0, -324, 270 };
	objects[2].s = { 324, 162, 324 };
	objects[2].r = 0;
	objects[2].material = { { { 0.7f, 0.7f, 1.0f }, 0.2f, 0,    RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 1.0f }, 0.7f, 0,    RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 1.0f }, 0.2f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.7f, 0.7f, 1.0f }, 0.0f, 0,    RT_PERFECT_SPECULAR } };
	objects[2].type = RT_BOX;

	RT_Vec3f aux = objects[2].p + objects[2].s;
	float r = (aux.x > aux.y) ? aux.x : aux.y;
	r = (aux.z > r) ? aux.z : r;

	float x0 = objects[2].p.x;
	float y0 = objects[2].p.y;
	float z0 = objects[2].p.z;
	float x1 = objects[2].p.x + r;
	float y1 = objects[2].p.y + r;
	float z1 = objects[2].p.z + r;

	objects[2].bbox = { x0, y0, z0,
		x1, y1, z1 };

	//memcpy(objects[2].invMatrix, (void*)m.GetMatrix(), sizeof(objects[2].invMatrix));
	//t->CopyTransformMatrix(objects[2].invMatrix);

}

void setScene(RT_Primitive *planes)
{
	planes[0] = { { 0, -324, 0 },{ 0,  1,  0 }, 0,
	{ { { 0.4f, 0.3f, 0.3f }, 0.2f, 0, RT_LAMBERTIAN },
	{ { 0.4f, 0.3f, 0.3f }, 0.7f, 0, RT_LAMBERTIAN },
	{ { 0.4f, 0.3f, 0.3f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
		RT_PLANE };
	planes[1] = { { 0, 0, 2419 },{ 0,  0, -1 }, 0,
	{ { { 0.6f, 0.5f, 0.5f }, 0.2f, 0, RT_LAMBERTIAN },
	{ { 0.6f, 0.5f, 0.5f }, 0.7f, 0, RT_LAMBERTIAN },
	{ { 0.6f, 0.5f, 0.5f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
		RT_PLANE };
	planes[2] = { { -1296, 0, 0 },{ 1,  0,  0 }, 0,
	{ { { 0.5f, 0.6f, 0.6f }, 0.2f, 0, RT_LAMBERTIAN },
	{ { 0.5f, 0.6f, 0.6f }, 0.7f, 0, RT_LAMBERTIAN },
	{ { 0.5f, 0.6f, 0.6f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
		RT_PLANE };
	planes[3] = { { 1296, 0, 0 },{ -1,  0,  0 }, 0,
	{ { { 0.5f, 0.6f, 0.6f }, 0.2f, 0, RT_LAMBERTIAN },
	{ { 0.5f, 0.6f, 0.6f }, 0.7f, 0, RT_LAMBERTIAN },
	{ { 0.5f, 0.6f, 0.6f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
		RT_PLANE };
	planes[4] = { { 0, 800, 0 },{ 0, -1,  0 }  , 0,
	{ { { 0.7f, 0.7f, 0.7f }, 0.2f, 0, RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 0.7f }, 0.7f, 0, RT_LAMBERTIAN },
	{ { 0.7f, 0.7f, 0.7f }, 0.5f, 1.0f, RT_GLOSSY_SPECULAR },
	{ { 0.7f, 0.7f, 0.7f }, 0.0f, 0.0f, RT_PERFECT_SPECULAR } },
		RT_PLANE };
}

void setLights(RT_Light *lights)
{
	lights[0].position = { 162.0f, 756.0f, 432.0f };
	lights[0].color = { 1, 1, 1 };
	lights[0].ls = 1.0f;
	lights[0].ex = 0.0f;
	lights[0].type = RT_POINT_LIGHT;

	lights[1].position = { -540.0f, 756.0f, 432.0f };
	lights[1].color = { 1, 1, 1 };
	lights[1].ls = 1.0f;
	lights[1].ex = 0.0f;
	lights[1].type = RT_POINT_LIGHT;
}


int main(int argc, char **argv)
{
	try
	{
		/*cria a aplicação OpenCL*/
		WORLD_GET->Set(ApplicationCLFactor::CreateApplicationUsersInput());

		//----------------------------------------------------------------------------------------------------------
		/*Cria os objetos*/
		const int numObjects = 3;
		RT_Primitive objs[numObjects];
		setObjects(objs);
		const int numPlanes = 5;
		RT_Primitive p[numPlanes];
		setScene(p);

		const int numLights = 2;
		RT_Light lights[numLights];
		setLights(lights);

		RT_ViewPlane vp = { 1920, 1080, { 1, 1 } };
		RT_Camera camera = { { -702, -108, -270},
							 {-540, -100, 0},
							 {0, 1.0f, 0},
								800, 1.5f, 0, 1,
								{}, {}, {} };
		camera.computeUVW();

		RT_DataScene world = { vp, {0, 0, 0}, numLights, numObjects + numPlanes };
		//---------------------------------------------------------------------------------------------------------

		/*Cria o buffer de leitura dos dados na GPU*/
		/*Cria os buffer de escrita na GPU*/
		Container *c = ContainerFactory::CreateContainer(
								{"world", "camera", 
								 "lights", "objects"},
								{ new Package<RT_DataScene>(),
								  new Package<RT_Camera>(),
								  new Package<RT_Light>() ,
								  new Package<RT_Primitive>() });

		//---------------------------------------------------------------------------------------------------------
		/*Empacota os dados*/
		for (int i = 0; i < numPlanes; i++)
		{
			c->AddElement("objects", p[i]);
		}
		for (int i = 0; i < numObjects; i++)
		{
			c->AddElement("objects", objs[i]);
		}

		c->AddElement("lights", lights[0]);
		c->AddElement("lights", lights[1]);

		c->AddElement("world", world);
		c->AddElement("camera", camera);

		//---------------------------------------------------------------------------------------------------------


		FinalProduct<int> f(1920*1080);
		f.Update();
		/*c->AddElement("in1", RT::Vec3f(2.5f, -3.0f, 1.0f))
		  .AddElement("in2", RT::Vec3f(2.5f, -1.0f, 0.5f));*/

		c->Update();
		c->ApplyBuffer();

		WORLD_GET_APP->Process(true);
		f.ApplyBuffer();

		Save(f.GetData(), 1920, 1080);
	}
	catch (const LogError &e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}