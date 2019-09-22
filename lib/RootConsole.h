#ifndef _H_CTK_ROOT_CONSOLE
#define _H_CTK_ROOT_CONSOLE
#include <SDL2/SDL.h>
#include "Console.h"
#include "TileRenderer.h"

class RootConsole : public Console
{
	public:
		RootConsole(unsigned, unsigned, SDL_Renderer*, const char*);
		virtual ~RootConsole() = default;

		void render();
		bool good() const { return good_; }
	private:
		SDL_Renderer* renderer_{ nullptr };
		TileRenderer tile_renderer_;
		bool good_ { true };
};
#endif
