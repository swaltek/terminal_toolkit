#ifndef H_CTK_TILESET
#define H_CTK_TILESET
#include "SDL2/SDL.h"

//Wrapper class for rendering tileset
class CTK_Tileset
{
	public:
		CTK_Tileset(SDL_Renderer*);
		CTK_Tileset(SDL_Renderer*, const char*);
		~CTK_Tileset();

		bool load_from_bmp(const char*);

		void render(int, int, char = '\n');

		void free();
	private:
		SDL_Texture* texture { NULL };

		SDL_Renderer* tile_renderer;

		SDL_Rect* tile_clips { NULL };
		unsigned tile_clips_size { 0 };

		int width { 0 };
		int height { 0 };
		int tile_width { 0 };
		int tile_height { 0 };
};
#endif
