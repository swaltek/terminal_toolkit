#ifndef H_CTK_TILE_RENDERER
#define H_CTK_TILE_RENDERER
#include <SDL2/SDL.h>
#include "ConsoleCell.h"
#include <memory>

//Wrapper class for rendering tileset
class TileRenderer
{
	public:
		TileRenderer(SDL_Renderer* renderer): renderer_(renderer) {};
		~TileRenderer();

		bool load_from_bmp(const char*);

		void free();

		SDL_Rect get_tile(const char) const;
		void render(const SDL_Rect&,const ConsoleCell&);

		int tile_width() const { return tile_width_; }
		int tile_height() const { return tile_height_; }
	private:
		int tiles_in_row() const { return width_ / tile_width_; }

		SDL_Renderer* renderer_ { nullptr };
		SDL_Texture* texture_ { nullptr };

		int width_ { 0 }; //of texture
		int height_ { 0 }; //of texture
		int tile_width_ { 0 }; //individual tile
		int tile_height_ { 0 }; //individual tile
};
#endif
