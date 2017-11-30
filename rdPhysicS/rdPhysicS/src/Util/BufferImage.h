#ifndef	__BUFFER_IMAGE_H__
#define	__BUFFER_IMAGE_H__

#include "..\GlobalDefs.h"
#include<SDL_image.h>
#include<SDL.h>

RDPS_BEGIN

	class BufferImage
	{
	private:
		SDL_Surface *image;
		SDL_Texture *texture;
		SDL_Rect rect;
		int width;
		int height;

	public:
		BufferImage(const int w, const int h);
		~BufferImage();

		void Set(const uint w, const uint h);

		uint GetWidth() const;
		uint GetHeight() const;

		void Draw(SDL_Renderer *renderer);
		void SwapBuffer(SDL_Renderer *renderer, const int *buffer);
		void Save();
	};

RDPS_END

#endif//__BUFFER_IMAGE_H__