#include <iostream>
#include <SDL.h>
#include "src\rdps-CL\includes_appCL.h"
#include "src\Util\LogError.h"
#include "src\rdps-packages\output\FinalProduct.h"
#include "src\rdps-packages\output\Renderer.h"
#include "src\World.h"
#include "src\scenes\Test.h"
#include "src\scenes\SceneTestAreaLight .h"
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
		rdps::World::Quality(VERY_HIGH);
		//Test t;
		//t.Draw();
		SceneTestAreaLight().Draw();

		Save(rdps::World::GetRenderer()->GetData(), 1920, 1080);

		//World::Resolution(LOW);
		//t.Draw();

		//Save(World::GetRenderer()->GetData(), 1920, 1080);
	}
	catch (const rdps::LogError &e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}