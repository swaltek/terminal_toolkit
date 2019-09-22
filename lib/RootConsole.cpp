#include "RootConsole.h"

#include "Console.h"
#include "ConsoleCell.h"
#include "TileRenderer.h"

RootConsole::~RootConsole()
{
	delete tile_renderer_;
}
void RootConsole::render()
{
	for(unsigned i{ 0 }; i < cell_count(); ++i)
	{
		int cell_x = (i % width()) * tile_renderer_->tile_width();
		int cell_y = (i / height()) * tile_renderer_->tile_height();
		SDL_Rect rect = 
			{ cell_x, cell_y, tile_renderer_->tile_width(), tile_renderer_->tile_height() };
		tile_renderer_->render( rect, cells_[i] );
	}
}
