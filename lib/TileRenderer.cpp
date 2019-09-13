#include "TileRenderer.h"

#include "SDL2/SDL.h"
#include <cstdio>

const unsigned TILESET_WIDTH = 16;
const unsigned TILESET_HEIGHT = 16;

TileRenderer::TileRenderer(SDL_Renderer* renderer): tile_renderer(renderer)
{
}
TileRenderer::TileRenderer(SDL_Renderer* renderer, const char* file_path): tile_renderer(renderer)
{
	load_from_bmp( file_path );
}

TileRenderer::~TileRenderer()
{
	tile_renderer = nullptr;
	free();
}

bool TileRenderer::load_from_bmp(const char* file_path)
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
		SDL_LockSurface( loaded_surface ); //Lock surface before messing with pixels
		unsigned first_pixel = static_cast<unsigned*>(loaded_surface->pixels)[0];
		SDL_UnlockSurface( loaded_surface ); //Unlock surface before changing color key

		if( SDL_SetColorKey( loaded_surface, SDL_TRUE, first_pixel ) )
		{
			printf( "Error color keying! SDL Error %s\n", SDL_GetError() );
		}

		new_texture = SDL_CreateTextureFromSurface( tile_renderer, loaded_surface );
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
				tile_clips[i].x = (i % TILESET_WIDTH) * tile_width;
				tile_clips[i].y = (i / TILESET_WIDTH) * tile_height;
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

void TileRenderer::render(int x, int y, char clip)
{
	SDL_Rect render_clip = { 0, 0, width, height };
	//if not rendering the entire image
	if( clip != '\n' ) render_clip = tile_clips[clip];

	SDL_Rect render_rect = { x * tile_width , y * tile_height, render_clip.w, render_clip.h };

	SDL_RenderCopy( tile_renderer, texture, &render_clip, &render_rect);
}

void TileRenderer::free()
{
	//Free existing texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;

		delete[] tile_clips;
		tile_clips = nullptr;
		tile_clips_size = 0;

		width = 0;
		height = 0;
		tile_width = 0;
		tile_height = 0;
	}
}
