#include "RootConsole.h"

#include "Console.h"
#include "ConsoleCell.h"
#include "TileRenderer.h"

RootConsole::RootConsole(unsigned height, unsigned width,SDL_Renderer* renderer, const char* bmp_path):
	Console(height,width), tile_renderer_(renderer)
{
	good_ = tile_renderer_.load_from_bmp(bmp_path);
}

void RootConsole::render()
{
		for(unsigned i{ 0 }; i < cell_count(); ++i)
		{
			int cell_x = (i % width()) * tile_renderer_.tile_width();
			int cell_y = (i / height()) * tile_renderer_.tile_height();
			SDL_Rect rect = 
				{ cell_x, cell_y, tile_renderer_.tile_width(), tile_renderer_.tile_height() };
			tile_renderer_.render( rect, cells_[i] );
		}
}
