#include <iostream>
#include <SDL.h>
#include "src\rdps.h"
#include "src\system\Window.h"
#include "src\scenes\Test.h"
#include "src\scenes\SceneTestAreaLight.h"
#include "src\scenes\RealTime.h"
#include <SDL_image.h>

int Save(const int *image, const int w, const int h)
{
	if (!image)
		return -1;

	SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	if (!img)
		rdps::Logger::Log("ERROR when saving the image");

	img->pixels = (cl_uint*)image;
	std::cout << "Digite um nome com a extencao(.png) para a imagem: ";
	char infoname[128];
	std::cin >> infoname;
	std::string name = IMAGE_PATH;
	name += infoname;

	IMG_SavePNG(img, name.c_str());

	//SDL_FreeSurface(img);

	return 0;
}

int main(int argc, char **argv)
{
	try
	{
		rdps::World::Init();
		rdps::World::SetViewPlane(1920, 1080);
		//Test t;
		//t.Init();
		//t.Draw();
		SceneTestAreaLight s; 
		s.Init();
		s.Draw();

		Save(rdps::World::GetRenderer()->GetData(), 1920, 1080);

		//World::Resolution(LOW);
		//t.Draw();

		//Save(World::GetRenderer()->GetData(), 1920, 1080);
	}
	catch (const rdps::LogError &e)
	{
		std::cout << e.what() << std::endl;
	}

	//rdps::Window(new RealTime(), "TESTE", 1920, 1080).Show();

	system("pause");
	return 0;
}