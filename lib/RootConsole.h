#ifndef _HPP_CTK_ROOT_CONSOLE
#define _HPP_CTK_ROOT_CONSOLE
#include <SDL2/SDL.h>
#include "Console.h"
#include "TileRenderer.h"

namespace TTK
{
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
}
#endif //_HPP_CTK_ROOT_CONSOLE
