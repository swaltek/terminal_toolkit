#include "Window.h"
#include "Console.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <iostream>

namespace TTK
{
  bool load_sdl()
  {
    bool success{ true };
    if (SDL_WasInit(SDL_INIT_VIDEO) != true)
    {
      std::clog << "[Info] SDL has not been init yet... starting SDL!"
                << std::endl;
      if (SDL_Init(SDL_INIT_VIDEO) != 0)
      {
        sdlerr(__FILE__, __LINE__);
        success = false;
      }
    }
    return success;
  }

  SDL_Window* Window::load_window()
  {
    good_ = load_sdl();
    if(!good_) return nullptr;

    SDL_Window* window = SDL_CreateWindow("RL",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               width_, height_, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
      sdlerr(__FILE__, __LINE__);
      good_ = false;
    }

    return window;
  }

  SDL_Renderer *Window::load_renderer()
  {
    SDL_Renderer *renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
      sdlerr(__FILE__, __LINE__);
      good_ = false;
    }
    return renderer;
  }

  TileRenderer Window::load_tile_renderer(const std::string &ts_path)
  {
    TileRenderer tile_renderer{renderer_};
    good_ = tile_renderer.load_from_bmp(ts_path.c_str());

    return tile_renderer;
  }

  Console Window::load_console()
  {
    uint c_width = width_ / tile_renderer_.tile_width();
    uint c_height = height_ / tile_renderer_.tile_height();
    return Console{c_width, c_height};
  }

  Window::Window(unsigned width, unsigned height, const char *tileset_path)
      : width_(width), height_(height)
      , window_(load_window())
      , renderer_(load_renderer())
      , tile_renderer_(load_tile_renderer(tileset_path))
      , console(load_console())
  {}

  Window::~Window()
  {
    close();
  }

  void Window::close()
  {
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    window_ = nullptr;
    renderer_ = nullptr;

    SDL_Quit();

    good_ = false;
  }


  void Window::render()
  {
    // int err = SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xff );
    // if( err ) printf("Error setting renderer drawcolor!");
    int err = SDL_RenderClear(renderer_);
    if (err)
      printf("Error clearing renderer!");

    tile_renderer_.render_console(console);

    SDL_RenderPresent(renderer_);
  }
}
