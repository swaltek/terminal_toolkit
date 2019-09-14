#ifndef H_CTK_TILE_RENDERER
#define H_CTK_TILE_RENDERER
#include "SDL2/SDL.h"

//Wrapper class for rendering tileset
class TileRenderer
{
	public:
		TileRenderer(SDL_Renderer* renderer): tile_renderer(renderer) {};
		~TileRenderer();

		bool load_from_bmp(const char*);

		void render(int, int, char = '\0') const;

		void free();
	private:
		SDL_Renderer* tile_renderer { nullptr };
		SDL_Texture* texture { nullptr };

		SDL_Rect* tile_clips { nullptr };
		unsigned tile_clips_size { 0 };

		int width { 0 }; //of texture
		int height { 0 }; //of texture
		int tile_width { 0 }; //individual tile
		int tile_height { 0 }; //individual tile
};
#endif
