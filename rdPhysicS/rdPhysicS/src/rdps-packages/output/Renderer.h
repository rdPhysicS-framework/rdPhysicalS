#ifndef	__RENDERER_H__
#define	__RENDERER_H__

#include "FinalProduct.h"

RDPS_BEGIN
	PKG_BEGIN

		class Renderer
		{
		private:
			FrameBuffer *buffer;

		public:
			Renderer(const int width = 1,
					 const int height = 1);
			Renderer(FrameBuffer *_buffer);
			~Renderer();

			FrameBuffer *GetBuffer() const;
			int *GetData() const;

			Renderer &operator=(const Renderer &other);
			Renderer &Update();
			Renderer &Render();
		};

	PKG_END

	void SwapBuffer(PKG Renderer &buff1, PKG Renderer &buff2);

RDPS_END

#endif//__RENDERER_H__