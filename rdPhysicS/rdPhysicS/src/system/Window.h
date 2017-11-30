#ifndef	__WINDOW_H__
#define	__WINDOW_H__

#include "..\GlobalDefs.h"
#include "..\rdps.h"

#include <SDL.h>
#include <SDL_image.h>

RDPS_BEGIN
	
	class BufferImage;

	class Window
	{
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Surface *image;
		SDL_Event event;

		uint width;
		uint height;

		std::string title;

		SceneBase *scene;

		BufferImage *bfImage;

		bool quit;
		double before;
		bool t;

	private:
		void Init();
		void Update();
		void Draw();
		void End();
		void Save();
		void Frame(Uint8 fps);

	public:
		Window(SceneBase *_scene, std::string _title, uint w, uint h);
		~Window();

		uint GetWidth() const;
		uint GetHeight() const;
		const SDL_Window *GetWindow() const;
		const SDL_Renderer *GetRenderer() const;

		void Loop();
		void Show();
		void VerifyEvents(SDL_Event &p_event);
		void Events();
	};

RDPS_END

#endif//__WINDOW_H__