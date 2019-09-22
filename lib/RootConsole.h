#ifndef _H_CTK_ROOT_CONSOLE
#define _H_CTK_ROOT_CONSOLE
#include <SDL2/SDL.h>
#include "Console.h"
#include "TileRenderer.h"

class RootConsole : public Console
{
	public:
		RootConsole(unsigned height, unsigned width,TileRenderer* t_renderer):
			Console(height ,width), tile_renderer_(t_renderer) {}
		virtual ~RootConsole() override;

		void render();
	private:
		TileRenderer* tile_renderer_;
};
#endif
