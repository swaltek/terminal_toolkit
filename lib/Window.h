#ifndef _H_TTK_WINDOW
#define _H_TTK_WINDOW
#include "Console.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>

namespace TTK
{
  bool init_sdl();
  
  class Window
  {
    public:
      Console* console{ nullptr };
      Window(unsigned, unsigned, const char* );
      ~Window();

      void render();
      const bool good() const { return good_; }
    private:
      void close();
      bool create();
      
      //---MEMBERS---
      SDL_Window* window_{ nullptr };
      SDL_Renderer* renderer_{ nullptr };	
      TileRenderer* tile_renderer_{ nullptr };
  
      unsigned width_;
      unsigned height_;

      void render_console();
      bool good_ { true };
  };
}
#endif //_H_TTK_WINDOW
