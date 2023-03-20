#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <cstdio>

namespace TTK
{
  const unsigned TILESET_WIDTH = 16;
  const unsigned TILESET_HEIGHT = 16;
  
  TileRenderer::~TileRenderer()
  {
    renderer_ = nullptr;
    free();
  }
  
  bool TileRenderer::load_from_bmp(const char* file_path)
  {
    free(); //Get rid of any already existing texture
  
    printf("Loading %s to TileRenderer\n", file_path);
    SDL_Texture* new_texture_ { NULL }; //Final  texture
    SDL_Surface* loaded_surface = SDL_LoadBMP( file_path );
  
    if(loaded_surface != nullptr )
    {
      //Color key image to first pixel
      unsigned first_pixel = static_cast<unsigned*>(loaded_surface->pixels)[0];
      if( SDL_SetColorKey( loaded_surface, SDL_TRUE, first_pixel ) != 0 )
      {
        printf( "Error color keying! SDL Error %s\n", SDL_GetError() );
      }
  
      new_texture_ = SDL_CreateTextureFromSurface( renderer_, loaded_surface );
      if( new_texture_ == nullptr )
      {
        printf( "Unable to create texture from %s! SDL Error: %s\n", file_path, SDL_GetError() );
      }
  
      width_ = loaded_surface->w;
      height_ = loaded_surface->h;
      tile_width_ = width_ / TILESET_WIDTH;
      tile_height_ = height_ / TILESET_HEIGHT;
  
      //Get rid of loaded surface
      SDL_FreeSurface( loaded_surface );
    }
    else
    {
      printf( "Unable to load bmp %s! SDL Error: %s\n", file_path, SDL_GetError() );
    }
    
  
    //return success
    texture_ = new_texture_ ;
    printf("Load %s!\n", texture_ != nullptr ? "successful" : "failed" );
    return texture_ != nullptr;
  }
  
  SDL_Rect TileRenderer::get_tile(const char c) const
  {
    int tile_x = (c % tiles_in_row()) * tile_width_;
    int tile_y = (c / tiles_in_row()) * tile_height_;
    return { tile_x, tile_y, tile_width_, tile_height_ };
  }
  
  void TileRenderer::render(const SDL_Rect& rect, const ConsoleCell& cell)
  {
    int err{0};
    //Draw background first
    err = SDL_SetRenderDrawColor(renderer_, cell.back_r, cell.back_g, cell.back_b, 0xff);
    if( err ) { printf("Error setting renderer draw color"); }
    err = SDL_RenderFillRect(renderer_, &rect);
    if( err ) { printf("Error filling rectangle"); }
  
    //Draw foreground
    SDL_Rect tile = get_tile(cell.c);
    err = SDL_SetTextureColorMod(texture_, cell.r, cell.g, cell.b);
    if( err ) { printf("error setting color mod!"); }
    SDL_RenderCopy( renderer_, texture_, &tile, &rect);
    if( err ) { printf("error render copy"); }
  }
  
  void TileRenderer::free()
  {
    //Free existing texture_ if it exists
    if( texture_ != nullptr )
    {
      SDL_DestroyTexture( texture_ );
      texture_ = nullptr;
  
      width_ = 0;
      height_ = 0;
      tile_width_ = 0;
      tile_height_ = 0;
    }
  }
}
