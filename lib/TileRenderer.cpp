#include "TileRenderer.h"

#include "SDL2/SDL.h"
#include <cstdio>

const unsigned TILESET_WIDTH = 16;
const unsigned TILESET_HEIGHT = 16;

TileRenderer::~TileRenderer()
{
	renderer_ = nullptr;
	free();
}

bool TileRenderer::load_from_bmp(const char* file_path)
{
	free(); //Get rid of any already existing texture_

	SDL_Texture* new_texture_ { NULL }; //Final new texture_
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

		new_texture_ = SDL_CreateTextureFromSurface( renderer_, loaded_surface );
		if( new_texture_ == NULL )
		{
			printf( "Unable to create texture_ from %s! SDL Error: %s\n", file_path, SDL_GetError() );
		}
		else
		{
			width_ = loaded_surface->w;
			height_ = loaded_surface->h;
			tile_width_ = width / TILESET_WIDTH;
			tile_height_ = height_ / TILESET_HEIGHT;

			tiles_size_ = TILESET_WIDTH * TILESET_HEIGHT;
			tiles_ = new SDL_Rect[ tiles_size_ ];
			for(unsigned i{ 0 }; i < tiles_size_ ; ++i )
			{
				tiles_[i].x = (i % TILESET_WIDTH) * tile_width_;
				tiles_[i].y = (i / TILESET_WIDTH) * tile_height_;
				tiles_[i].w = tile_width_;
				tiles_[i].h = tile_height_;
			}
		}

		//Get rid of loaded surface
		SDL_FreeSurface( loaded_surface );
	}

	//return success
	texture_ = new_texture_;
	return texture_ != NULL;
}

void TileRenderer::render(int x, int y, char clip) const
{
	SDL_Rect render_clip = { 0, 0, width_, height_ };

	//if not rendering the entire image
	if( clip != '\0' ) render_clip = tiles_[clip];

	SDL_Rect render_rect = { x, y, render_clip.w, render_clip.h };

	SDL_RenderCopy( renderer_, texture_, &render_clip, &render_rect);
}

void TileRenderer::free()
{
	//Free existing texture_ if it exists
	if( texture_ != NULL )
	{
		SDL_DestroyTexture( texture_ );
		texture_ = NULL;

		delete[] tiles_;
		tiles_ = nullptr;
		tiles_size_ = 0;

		width_ = 0;
		height_ = 0;
		tile_width_ = 0;
		tile_height_ = 0;
	}
}
