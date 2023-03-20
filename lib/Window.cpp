#include "Window.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>

namespace TTK
{
  Window::Window(unsigned width, unsigned height,const char* tileset_path)
    : width_(width), height_(height)
  {
    if(SDL_WasInit(SDL_INIT_VIDEO) != true)
    {
      printf("SDL has not been init yet... Trying to init SDL!\n");
      good_ = init_sdl();
      printf( "Init of SDL was %s!\n", good_ ? "Successful" : "Failed" );
    }
  
    if(good_)
    {
      good_ = create();
      if(good_)
      {
        TileRenderer* t_renderer = new TileRenderer( renderer_ );
        good_ = t_renderer->load_from_bmp(tileset_path);
        tile_renderer_ = t_renderer;
  
        console = new Console(10, 10);
  
        if( !good_ ) printf("Failed to create root console!\n");
      }
    }
  }
  
  Window::~Window()
  {
    close();
  }
  
  void Window::close()
  {
    SDL_DestroyWindow( window_ );
    SDL_DestroyRenderer( renderer_ );
    window_ = nullptr;
    renderer_ = nullptr;
  
    delete tile_renderer_;
    tile_renderer_ = nullptr;
    console = nullptr;
  
    SDL_Quit();
  
    good_ = false;
  }
  
  bool Window::create()
  {
    window_ = SDL_CreateWindow( "RL",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        width_, height_, SDL_WINDOW_SHOWN );
    if( window_ == nullptr )
    {
      printf( "Failure to create window! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
      renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED );
      if( renderer_ == nullptr )
      {
        printf( "Failure to create renderer! SDL Error: %s\n", SDL_GetError() );
      }
    }
  
    return renderer_ != nullptr;
  }

  void Window::render()
  {
		//int err = SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xff );
  //  if( err ) printf("Error setting renderer drawcolor!");
		int err = SDL_RenderClear( renderer_ );
    if( err ) printf("Error clearing renderer!");

    render_console();

		SDL_RenderPresent( renderer_ );
  }

  void Window::render_console()
  {
    auto cells = console->cells();
    for(unsigned i{ 0 }; i < console->cell_count(); ++i)
    {
      int cell_x = (i % console->width()) * tile_renderer_->tile_width();
      int cell_y = (i / console->height()) * tile_renderer_->tile_height();
      SDL_Rect rect = 
        { cell_x, cell_y, tile_renderer_->tile_width(), tile_renderer_->tile_height() };
      tile_renderer_->render( rect, cells[i] );
    }
  }
  
  bool init_sdl()
  {
    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
      printf( "Failure to init SDL! SDL Error: %s\n", SDL_GetError() );
      return false;
    }
    return true;
  }
}
