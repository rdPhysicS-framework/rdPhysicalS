#include "Renderer.h"
#include "..\..\World.h"
#include "..\..\rdps-CL\Application\ApplicationCL.h"

USING_RDPS
USING_PKG

Renderer::Renderer(const int width, 
				   const int height) :
		  buffer(new FrameProduct(width*height))
{}

Renderer::Renderer(FrameProduct *_buffer) :
	buffer(_buffer)
{}

Renderer::~Renderer()
{
	if (buffer)
		delete buffer;
}

Renderer &Renderer::operator=(const Renderer &other)
{
	*buffer = *other.buffer;
	return (*this);
}

Renderer &Renderer::Update()
{
	buffer->Update();
	return (*this);
}

Renderer &Renderer::Render()
{
	buffer->Update();
	WORLD_GET_APP->Process(true);
	buffer->ApplyBuffer();
	return (*this);
}

void SwapBuffer(Renderer &buff1, Renderer &buff2)
{
	buff1 = buff2;
}
