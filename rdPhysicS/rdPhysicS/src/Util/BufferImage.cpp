#include "BufferImage.h"
#include "..\Util\LogError.h"

USING_RDPS

BufferImage::BufferImage(const int w, const int h) :
			 image(nullptr),
			 texture(nullptr),
			 rect({0, 0, w, h}),
			 width(w), 
			 height(h)
{
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, RMASK, GMASK, BMASK, AMASK);
	if (!image)
		rdps::Logger::Log(SDL_GetError());
}

BufferImage::~BufferImage()
{
	image->pixels = nullptr;
	SDL_FreeSurface(image);

	if (texture)
		SDL_DestroyTexture(texture);
}

void BufferImage::Set(const uint w, const uint h)
{
	rect.w = width = w;
	rect.h = height = h;
}

uint BufferImage::GetWidth() const
{
	return width;
}

uint BufferImage::GetHeight() const
{
	return height;
}

void BufferImage::Draw(SDL_Renderer * renderer)
{
	if(renderer)
		SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void BufferImage::SwapBuffer(SDL_Renderer *renderer, const int *buffer)
{
	if(texture)
		SDL_DestroyTexture(texture);

	image->pixels = (uint*)buffer;

	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGBA(image->format, 0, 0, 0, 255));

	texture = SDL_CreateTextureFromSurface(renderer, image);

	if (!texture)
		Logger::Log(SDL_GetError());

}

void BufferImage::Save()
{
	std::cout << "Digite um nome com a extencao(.png) para a imagem: ";
	char infoname[128];
	std::cin >> infoname;
	std::string name = IMAGE_PATH;
	name += infoname;

	IMG_SavePNG(image, name.c_str());
}
