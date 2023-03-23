#include "display/Window.h"
#include <SDL2/SDL.h>
#include <entt/entt.hpp>

#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace TTK;

std::vector<std::vector<bool>> map;

typedef std::mt19937 Rng;
Rng rng;

void map_to_console(Console& console)
{
  int y{0};
  for(auto row : map){
    int x{0};
    for(auto cell : row){
      std::string val = (cell) ? "." : "#";
      console.set_char(x, y, val[0]);
      console.set_color(x, y, 0xff, 0x00, 0xff);
      console.set_back_color(x, y, 0xff, 0xff, 0xff);
      x++;
    }
    y++;
  }
}

void init_game( size_t width, size_t height)
{
  uint32_t seed_val = 234;
  rng.seed(seed_val);

  std::vector<bool> row(width, false);
  map = std::vector<std::vector<bool>>(height, row);

  std::uniform_int_distribution<int> dir_dist(0, 3);
    
    int x_pos = width / 2, y_pos = height / 2;
    const int k_step_count = 2500;
    for(int i = 0; i < k_step_count; i++)
    {
      int direction = dir_dist(rng);
      int x_chg = 0, y_chg =0;
      switch(direction){
        case 0:
          x_chg = 1;
          break;
        case 1:
          x_chg = -1;
          break;
        case 2:
          y_chg = 1;
          break;
        case 3:
          y_chg = -1;
          break;
      }

      int x_new = x_pos + x_chg, y_new = y_pos + y_chg;
      if(x_chg != 0 && 1 < x_new && x_new < width - 1){
        x_pos = x_new;
      }
      if(y_chg != 0 && 1 < y_new && y_new < height - 1){
        y_pos = y_new;
      }

      map[y_pos][x_pos] = true;
    }
}

float frame_cap{ 60 };
float ms_per_frame{ 1000.0f / frame_cap };
float fps{ 0 };

void delay_step(uint64_t start_counter, uint64_t end_counter)
{
    //mulitplying by 1000.0f to convert to ms
    float elapsed_ms = ((end_counter - start_counter) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
    if( elapsed_ms < ms_per_frame )
    {
      float ms_left = ms_per_frame - elapsed_ms;
      SDL_Delay( floor(ms_left) );

      //loop for the amount of time that could not be delayed with SDL_Delay
      float missed_ms = ms_left - floor(ms_left);
      start_counter = SDL_GetPerformanceCounter();
      float delayed_ms { 0 };
      while(delayed_ms < missed_ms)
      {
        end_counter = SDL_GetPerformanceCounter();
        delayed_ms = ((end_counter - start_counter) / (float)SDL_GetPerformanceFrequency()) * 1000.0f;
      }
      //adding time delayed to elapsed time of frame for fps calculation
      elapsed_ms += floor(ms_left) + delayed_ms;
      // floor(ms_left) is time delayed using SDL_Delay
      // this has a chance to be inaccurate if SDL_Delay 
      // delays more then floor(ms_left) due to OS sceduling
    }
    //dividing by 1000.0f to convert to seconds
    fps = 1.0f / (elapsed_ms / 1000.0f);
}

struct position{
  int x;
  int y;
};

enum action_t{
  no_action,
  move_action,
};

struct actionable{
  action_t t;
  float progress;
  float goal;
};
position player_pos_change{0, 0}; //held in actionable somehow TODO

int main()
{
  Window window(1280, 720, "art/curses_640x300.bmp");
  if(!window.good()){
    return -1;
  }

  init_game(window.console.width(), window.console.height());

  entt::registry registry{};
  const auto entity = registry.create();
  registry.emplace<position>(entity,window.console.width() / 2 , window.console.height() / 2);
  registry.emplace<actionable>(entity, no_action,0, 0);

  uint64_t start_counter;
  uint64_t end_counter;

  bool quit{ false };
  while( quit != true )
  {
    start_counter = SDL_GetPerformanceCounter();

    // HANDLE INPUT
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
      if( e.type == SDL_QUIT) quit = true;

      if( e.type == SDL_KEYDOWN )
      {
        switch( e.key.keysym.sym )
        {
          case SDLK_a:
            player_pos_change.x -= 1;
          break;
          case SDLK_d:
            player_pos_change.x += 1;
          break;
          case SDLK_w:
            player_pos_change.y -= 1;
          break;
          case SDLK_s:
            player_pos_change.y += 1;
          break;
        }
      }
    }

    map_to_console(window.console);

    auto pos_view = registry.view<position, actionable>();
    pos_view.each([&window, &player_pos_change](auto &pos, auto& actionable) {
      if(actionable.t == move_action){
        actionable.progress += 0.1; //TODO base on time step
        //TODO move draw code elsewhere aswell
        std::stringstream ss;
        ss << std::string((int)actionable.progress, '*');
        ss << std::string((int) actionable.goal - (int) actionable.progress, '-');
        window.console.print(pos.x - ((int)actionable.goal/2), pos.y + 2,ss.str());

        if (actionable.progress > actionable.goal ){
          actionable.t = no_action;
          if( player_pos_change.x ){
            pos.x += player_pos_change.x > 0 ? 1 : -1;
          }
          if( player_pos_change.y ){
            pos.y += player_pos_change.y > 0 ? 1 : -1;
          }
          player_pos_change = {0, 0};
        }
      }else if(actionable.t == no_action){
        if( player_pos_change.x || player_pos_change.y ){
          actionable.t = move_action;
          actionable.progress = 0;
          actionable.goal = 4;
        }
      }
      //TODO handle move elsewhere
      window.console.set_char(pos.x, pos.y, '@');
    });

    //fps counter
    std::string fps_string = std::to_string(fps);
    fps_string = fps_string.substr(0, fps_string.find('.') + 2);
    window.console.print(0, 0, fps_string);

    //render console
    window.render();
    window.console.clear();

    //UPDATE TIMESTEP AND FPS
    end_counter = SDL_GetPerformanceCounter();
    delay_step(start_counter, end_counter);
  }
  return 0;
}
