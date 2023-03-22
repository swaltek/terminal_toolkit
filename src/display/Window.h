#ifndef _H_TTK_WINDOW
#define _H_TTK_WINDOW
#include "Console.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

namespace TTK
{
  inline void sdlerr(const std::string file, int line){
      std::cerr << "[ERROR]"
        << file << ":" << line
        << " SDL_Error: "<< SDL_GetError() << std::endl;
  }

  bool init_sdl();
  
  class Window
  {
    public:
      Window(unsigned, unsigned, const char* );
      ~Window();

      void render();
      const bool good(){ return good_; }

    private:
      SDL_Window* load_window();
      SDL_Renderer* load_renderer();
      TileRenderer load_tile_renderer(const std::string&);
      Console load_console();
      void close();

      bool good_ { true };
      unsigned width_;
      unsigned height_;
      
      SDL_Window* window_{ nullptr };
      SDL_Renderer* renderer_{ nullptr };	
      TileRenderer tile_renderer_;
      public: Console console;
  
  };
}
#endif //_H_TTK_WINDOW
