#include "RootConsole.h"
#include "Console.h"
#include "ConsoleCell.h"
#include "TileRenderer.h"

RootConsole::RootConsole(unsigned height, unsigned width,SDL_Renderer* renderer, const char* bmp_path):
	Console(height,width), renderer_(renderer), tile_renderer_(renderer)
{
	good_ = tile_renderer_.load_from_bmp(bmp_path);
}

void RootConsole::render()
{
		for(unsigned i{ 0 }; i < width() * height(); ++i)
		{
			int cell_x = i % height();
			int cell_y = i / width();
			SDL_Rect cell_rect
				{
					cell_x * tile_renderer_.tile_width(),
					cell_y * tile_renderer_.tile_height(),
					tile_renderer_.tile_width(),
					tile_renderer_.tile_height()
				};
			const ConsoleCell& cell = cells_[i];
			//render background
			SDL_SetRenderDrawColor(renderer_, cell.back_r, cell.back_g, cell.back_b, 0xff);
			SDL_RenderFillRect(renderer_, &cell_rect);
			//render symbol
			tile_renderer_.set_color(cell.r, cell.g, cell.b);
			tile_renderer_.render(
					cell_rect.x,
					cell_rect.y,
					cell.c);
		}
}
