#ifndef H_CTK_TILESET
#define H_CTK_TILESET
#include "SDL2/SDL.h"

//Wrapper class for rendering tileset
class CTK_Tileset
{
	public:
		CTK_Tileset();
		CTK_Tileset(char*);
		~CTK_Tileset();

		bool load_from_file(const char*);

		void render(int, int, char = '\n');

		void free();
	private:
		SDL_Texture* texture { NULL };

		SDL_Rect* tile_clips { NULL };
		unsigned tile_clips_size { 0 };

		unsigned width { 0 };
		unsigned height { 0 };
		unsigned tile_width { 0 };
		unsigned tile_height { 0 };
}
#endif
