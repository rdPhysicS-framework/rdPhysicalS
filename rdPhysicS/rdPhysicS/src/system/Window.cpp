#include "Window.h"
#include "..\Util\BufferImage.h"
#include "Keyboard.h"

USING_RDPS

Window::Window(SceneBase *_scene, 
			   std::string _title,
			   uint w, uint h) :
		window(nullptr),
		renderer(nullptr),
	    width(w),
		height(h),
		title(_title),
		scene(_scene),
		bfImage(new BufferImage(w, h)),
		quit(false),
		t(false)
{}

Window::~Window()
{
	delete bfImage;
}

uint Window::GetWidth() const
{
	return width;
}

uint Window::GetHeight() const
{
	return height;
}

const SDL_Window *Window::GetWindow() const
{
	return window;
}

const SDL_Renderer *Window::GetRenderer() const
{
	return renderer;
}

void Window::Init()
{
	rdps::World::Init();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		Logger::Log(SDL_GetError());

	window = SDL_CreateWindow(title.c_str(),
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  width, height, SDL_WINDOW_SHOWN);

	if(!window)
		Logger::Log(SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED |
								  SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
		Logger::Log(SDL_GetError());

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	int png = IMG_INIT_PNG;

	if (!(IMG_Init(png) & png))
		Logger::Log(IMG_GetError());

	rdps::World::SetViewPlane(width, height);
}

void Window::Loop()
{
	scene->Init();

	before = SDL_GetTicks();

	while (!Keyboard::GetInstance()->IsDown(SDLK_ESCAPE))
	{
		Update();
		Draw();
		Frame(30);
	}
}

void Window::Update()
{
	float time = (SDL_GetTicks() - (before-1)) / 30.f;

	scene->Update(time);
}

void Window::Draw()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//if (!t)
	//{
	scene->Draw();
		//t = true;
	//}
}

void Window::End()
{
	if (window)
		SDL_DestroyWindow(window);
	if (renderer)
		SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
}

void Window::Save()
{
	char r = ' ';
	std::cout << "Deseja salvar o ultimo frame renderizado(precine s ou S para salvar)? ";

	std::cin >> r;

	if (r == 's' || r == 'S')
		bfImage->Save();
}

void Window::Frame(Uint8 fps)
{
	fps = (fps <= 0) ? 1 : 0;
	
	int ms = (1000 / fps) - SDL_GetTicks() + before;

	if(ms > 0)
		SDL_Delay(ms);
	
	before = SDL_GetTicks();

	Keyboard::GetInstance()->Update();
	Events();

	bfImage->SwapBuffer(renderer, World::GetRenderer()->GetData());
	bfImage->Draw(renderer);

	SDL_RenderPresent(renderer);
}

void Window::Show()
{
	try
	{
		Init();
		Loop();
		End();
		Save();
	}
	catch (const rdps::LogError &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Window::VerifyEvents(SDL_Event & p_event)
{
}

void Window::Events()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Keyboard::GetInstance()->Set(SDLK_ESCAPE, SDL_KEYDOWN);
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			Keyboard::GetInstance()->Set(event.key.keysym.sym, event.type);
			break;
		}
	}
}
