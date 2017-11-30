#include "Keyboard.h"

USING_RDPS

Keyboard *Keyboard::INSTANCE = nullptr;

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
	delete INSTANCE;

	releasedKeys.clear();
	pressedKeys.clear();
	downKeys.clear();
}

Keyboard *Keyboard::GetInstance()
{
	if (!INSTANCE)
	{
		INSTANCE = new Keyboard();
	}

	return INSTANCE;
}

bool Keyboard::IsPressed(SDL_Keycode key)
{
	return (pressedKeys.find(key) != pressedKeys.end() &&
			pressedKeys[key] != false);
}

bool Keyboard::IsDown(SDL_Keycode key)
{
	return (downKeys.find(key) != downKeys.end() &&
			downKeys[key] != false);
}

bool Keyboard::IsReleased(SDL_Keycode key)
{
	return (releasedKeys.find(key) != releasedKeys.end() &&
			releasedKeys[key] != false);
}

void Keyboard::Set(SDL_Keycode key, Uint32 action)
{
	if (action == SDL_KEYDOWN)
	{
		downKeys[key] = true;
		pressedKeys[key] = true;
	}
	else if (action == SDL_KEYUP)
	{
		downKeys.erase(key);
		releasedKeys[key] = true;
	}
}

void Keyboard::Update()
{
	pressedKeys.clear();
	releasedKeys.clear();
}
