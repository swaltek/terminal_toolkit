#ifndef H_CTK_TILE_RENDERER
#define H_CTK_TILE_RENDERER
#include "SDL2/SDL.h"

//Wrapper class for rendering tileset
class TileRenderer
{
	public:
		TileRenderer(SDL_Renderer* renderer): renderer_(renderer) {};
		~TileRenderer();

		bool load_from_bmp(const char*);

		void render(int, int, char = '\0') const;

		void free();
	private:
		SDL_Renderer* renderer_ { nullptr };
		SDL_Texture* texture_ { nullptr };

		SDL_Rect* tiles_ { nullptr };
		unsigned tiles_size_ { 0 };

		int width_ { 0 }; //of texture
		int height_ { 0 }; //of texture
		int tile_width_ { 0 }; //individual tile
		int tile_height_ { 0 }; //individual tile
};
#endif
