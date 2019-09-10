#include "CTK_Console.h"

#include "SDL2/SDL.h"
#include <cstdio>

const unsigned TILESET_WIDTH = 16;
const unsigned TILESET_HEIGHT = 16;

CTK_Tileset::CTK_Tileset(const char* file_path)
{
	load_from_bmp( file_path );
}

CTK_Tileset::~CTK_Tileset()
{
	free();
}

CTK_Tileset::load_from_bmp(const char* file_path)
{
	free(); //Get rid of any already existing texture

	SDL_Texture* new_texture { NULL }; //Final new texture
	SDL_Surface* loaded_surface = SDL_LoadBMP( file_path );//Load image from path

	if(loaded_surface == NULL )
	{
		printf( "Unable to load bmp %s! SDL Error: %s\n", file_path, SDL_GetError() );
	}
	else
	{
		//Color key image to first pixel
		SDL_LockTexture( loaded_surface ); //Lock surface before messing with pixels
		void * first_pixel = loaded_surface->pixels[0];
		SDL_UnlockSurface( loaded_surface ); //Unlock surface before changing color key
		if( SDL_SetColorKey( loaded_surface, SDL_TRUE, first_pixel ) )
		{
			printf( "Error color keying! SDL Error %s\n", SDL_GetError() );
		}

		new_texture = SDL_CreateTextureFromSurface( CTK_Renderer, loaded_surface );
		if( new_texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError() );
		}
		else
		{
			width = loaded_surface->w;
			height = loaded_surface->h;
			tile_width = width / TILESET_WIDTH;
			tile_height = height / TILESET_HEIGHT;

			tile_clips_size = TILESET_WIDTH * TILESET_HEIGHT;
			tile_clips = new SDL_Rect[ tile_clips_size ];
			for(unsigned i{ 0 }; i < tile_clips_size ; ++i )
			{
				tile_clips[i].x = i * tile_width;
				tile_clips[i].y = (i % TILESET_WIDTH) * tile_height;
				tile_clips[i].w = tile_width;
				tile_clips[i].h = tile_height;
			}
		}

		//Get rid of loaded surface
		SDL_FreeSurface( loaded_surface );
	}

	//return success
	texture = new_texture;
	return texture != NULL;
}

CTK_Tileset::render(int x, int y, char clip)
{
	SDL_Rect render_clip = { 0, 0, width, height };
	//if not rendering the entire image
	if( clip != '\n' ) render_clip = &tile_clips[clip];

	SDL_Rect render_rect = { x, y, render_clip.w, render_clip.h };
	SDL_RenderCopy( CTK_Renderer, texture, render_clip, &render_rect);
}

CTK_Tileset::free()
{
	//Free existing texture if it exists
	if( texture !- NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;

		delete[] tile_clips;
		tile_clips = NULL;
		tile_clips_size = NULL;

		width = 0;
		height = 0;
		tile_width = 0;
		tile_height = 0;
	}
}
