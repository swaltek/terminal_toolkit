#ifndef H_CTK_WINDOW
#define H_CTK_WINDOW
#include "TileRenderer.h"

#include <SDL2/SDL.h>

class Window
{
	public:
		Window(unsigned, unsigned, const char* );
		~Window();
		void close();
		void run();

		const bool good() const { return good_; }
	private:
		bool init_sdl();
		
		//---MEMBERS---
		SDL_Window* window_{ nullptr };
		SDL_Renderer* renderer_{ nullptr };
		TileRenderer* tile_renderer_{ nullptr };

		unsigned width_;
		unsigned height_;

		bool good_ { true };
};
#endif
