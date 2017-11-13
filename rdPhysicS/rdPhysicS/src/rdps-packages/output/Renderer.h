#ifndef	__RENDERER_H__
#define	__RENDERER_H__

#include "FinalProduct.h"

RDPS_BEGIN
	PKG_BEGIN

		class Renderer
		{
		private:
			FrameProduct *buffer;

		public:
			Renderer(const int width = 1,
					 const int height = 1);
			Renderer(FrameProduct *_buffer);
			~Renderer();

			inline FrameProduct *GetBuffer() const { return buffer; }
			inline int *GetData() const { return buffer->GetData(); }

			Renderer &operator=(const Renderer &other);
			Renderer &Update();
			Renderer &Render();
		};

	PKG_END

	void SwapBuffer(PKG Renderer &buff1, PKG Renderer &buff2);

RDPS_END

#endif//__RENDERER_H__