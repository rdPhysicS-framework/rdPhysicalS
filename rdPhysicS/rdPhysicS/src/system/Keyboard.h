#ifndef	__KEYBOARD_H__
#define	__KEYBOARD_H__

#include "..\GlobalDefs.h"
#include <SDL.h>
#include <unordered_map>

RDPS_BEGIN

	class Keyboard
	{
	private:
		std::unordered_map<SDL_Keycode, bool> pressedKeys;
		std::unordered_map<SDL_Keycode, bool> downKeys;
		std::unordered_map<SDL_Keycode, bool> releasedKeys;

		static Keyboard *INSTANCE;

		Keyboard();

	public:
		~Keyboard();

		static Keyboard *GetInstance();
		bool IsPressed(SDL_Keycode key);
		bool IsDown(SDL_Keycode key);
		bool IsReleased(SDL_Keycode key);
		void Set(SDL_Keycode key, Uint32 action);
		void Update();
	};

RDPS_END

#endif//__KEYBOARD_H__