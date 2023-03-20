#include "../lib/Window.h"
#include <SDL2/SDL.h>

using namespace TTK;

int main()
{
	Window window(640, 300, "data/art/curses_640x300.bmp");
	if(!window.good()){
		return -1;
	}

	//timestep
	float frame_cap{ 60 };
	float ms_per_frame{ 1000.0f / frame_cap };
	float fps{ 0 };
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
			/*
			else if( e.type == SDL_KEYDOWN )
			{
				switch( e.key.keysym.sym )
				{
				}
			}
			*/
		}

		// UPDATE
		//fps counter
		std::string fps_string = std::to_string(fps);
		fps_string = fps_string.substr(0, fps_string.find('.') + 2);
		window.console->print(0, 0, fps_string);

		//test code
		window.console->set_char(2, 2, 3);
		window.console->set_color(2, 2, 0xff, 0x00, 0xff);
		window.console->set_back_color(2, 2, 0xff, 0xff, 0xff);

		//render console
		window.render();
		window.console->clear();

		//UPDATE TIMESTEP AND FPS
		end_counter = SDL_GetPerformanceCounter();
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
			/*floor(ms_left) is time delayed using SDL_Delay
			this has a chance to be inaccurate if SDL_Delay 
			delays more then floor(ms_left) due to OS sceduling*/
		}
		//dividing by 1000.0f to convert to seconds
		fps = 1.0f / (elapsed_ms / 1000.0f);
	}
	return 0;
}
