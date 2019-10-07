#ifndef _H_TTK_WINDOW
#define _H_TTK_WINDOW
#include "RootConsole.h"

#include <SDL2/SDL.h>

namespace TTK
{
	bool init_sdl();
	
	class Window
	{
		public:
			Window(unsigned, unsigned, const char* );
			~Window();
			void run();
	
			const bool good() const { return good_; }
		private:
			void close();
			bool create();
			
			//---MEMBERS---
			SDL_Window* window_{ nullptr };
			SDL_Renderer* renderer_{ nullptr };
			RootConsole* root_console_{ nullptr };
	
			unsigned width_;
			unsigned height_;
	
			bool good_ { true };
	};
}
#endif //_H_TTK_WINDOW
