#include "Renderer.h"
#include "..\..\World.h"
#include "..\..\rdps-CL\Application\ApplicationCL.h"
#include "..\output\FinalProduct.h"

USING_RDPS
USING_PKG

Renderer::Renderer(const int width, 
				   const int height) :
		  buffer(new FrameBuffer(width*height))
{}

Renderer::Renderer(FrameBuffer *_buffer) :
	buffer(_buffer)
{}

Renderer::~Renderer()
{
	if (buffer)
		delete buffer;
}

FrameBuffer *Renderer::GetBuffer() const
{
	return buffer;
}

int *Renderer::GetData() const
{
	return buffer->GetData();
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
	World::Draw();
	buffer->ApplyBuffer();
	return (*this);
}

void SwapBuffer(Renderer &buff1, Renderer &buff2)
{
	buff1 = buff2;
}
