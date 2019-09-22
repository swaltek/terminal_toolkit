#include "Window.h"

#include "RootConsole.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>

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

			root_console_ = new RootConsole(10, 10, t_renderer);

			if( !good_ ) printf("Failed to create root console!\n");
		}
	}
}

Window::~Window()
{
	close();
}

void Window::run()
{
	//INIT
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
		root_console_->print(0, 0, fps_string);

		//test code
		root_console_->set_char(2, 2, 3);
		root_console_->set_color(2, 2, 0xff, 0x00, 0xff);
		root_console_->set_back_color(2, 2, 0xff, 0xff, 0xff);

		// RENDER
		//clear screen
		SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xff );
		SDL_RenderClear( renderer_ );

		//render console
		root_console_->render();
		root_console_->clear();

		//update
		SDL_RenderPresent( renderer_ );

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
}

void Window::close()
{
	SDL_DestroyWindow( window_ );
	SDL_DestroyRenderer( renderer_ );
	window_ = nullptr;
	renderer_ = nullptr;

	delete root_console_;
	root_console_ = nullptr;

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

bool init_sdl()
{
	if( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		printf( "Failure to init SDL! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	return true;
}
