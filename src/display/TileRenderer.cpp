#include "Window.h"
#include "TileRenderer.h"
#include "Console.h"

#include <SDL2/SDL.h>
#include <iostream>
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
  
    std::clog << "[Info] Loading " << file_path << " into TileRenderer\n";
    SDL_Texture* new_texture { nullptr }; //Final  texture
    SDL_Surface* loaded_surface = SDL_LoadBMP( file_path );
  
    if(loaded_surface != nullptr )
    {
      //Color key image to first pixel
      unsigned first_pixel = static_cast<unsigned*>(loaded_surface->pixels)[0];
      if( SDL_SetColorKey( loaded_surface, SDL_TRUE, first_pixel ) != 0 )
      {
        sdlerr(__FILE__, __LINE__);
      }
  
      new_texture = SDL_CreateTextureFromSurface( renderer_, loaded_surface );
  
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
    texture_ = new_texture;
    printf("[info] Loading texture was %s!\n", texture_ != nullptr ? "successful" : "failed" );
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
    if( err ) { printf("Error setting renderer draw color\n"); }
    err = SDL_RenderFillRect(renderer_, &rect);
    if( err ) { printf("Error filling rectangle\n"); }
  
    //Draw foreground
    SDL_Rect tile = get_tile(cell.c);
    if(SDL_SetTextureColorMod(texture_, cell.r, cell.g, cell.b) != 0)
      sdlerr(__FILE__, __LINE__);
    if(SDL_RenderCopy( renderer_, texture_, &tile, &rect) != 0)
      sdlerr(__FILE__,__LINE__);
  }

  void TileRenderer::render_console(const Console& console)
  {
    auto cells = console.cells();
    for(unsigned i{ 0 }; i < console.cell_count(); ++i)
    {
      int cell_x = (i % console.width()) * tile_width();
      int cell_y = (i / console.width()) * tile_height();
      SDL_Rect rect = 
        { cell_x, cell_y, tile_width(), tile_height() };
      render( rect, cells[i] );
    }
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
