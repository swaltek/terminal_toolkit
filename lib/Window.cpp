#include "Window.h"

#include "Console.h"
#include "TileRenderer.h"

#include <SDL2/SDL.h>
#include <cstdio>

Window::Window(unsigned width, unsigned height,const char* tileset_path)
	: width_(width), height_(height)
{
	if(init_sdl() != true)//init was unsuccsesfull
	{
		printf("Failure to init window!");
		good_ = false;
	}
	else
	{
		tile_renderer_ = new TileRenderer( renderer_ );
		if( tile_renderer_->load_from_bmp(tileset_path) != true ) good_ = false;
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

	SDL_Quit();

	good_ = false;
}

void Window::run()
{

	Console console{ 10, 10 };
	bool quit{ false };
	while( quit != true )
	{
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
		console.set_char(2, 2, 3);
		console.set_color(2, 2, 0xff, 0x00, 0xff);
		console.set_back_color(2, 2, 0xff, 0xff, 0xff);
		console.print(0, 0, "Hello, World!");
		console.print(5, 9, "Hello, World!");

		// RENDER
		//clear screen
		//background color will be black
		SDL_SetRenderDrawColor( renderer_, 0x00, 0x00, 0x00, 0xff );
		SDL_RenderClear( renderer_ );

		//render console
		for(unsigned i{ 0 }; i < console.width_ * console.height_; ++i)
		{
			int cell_x = i % console.height_;
			int cell_y = i / console.width_;
			SDL_Rect cell_rect
				{
					cell_x * tile_renderer_->tile_width(),
					cell_y * tile_renderer_->tile_height(),
					tile_renderer_->tile_width(),
					tile_renderer_->tile_height()
				};
			const ConsoleCell& cell = console.cells_[i];
			//render background
			SDL_SetRenderDrawColor(renderer_, cell.back_r, cell.back_g, cell.back_b, 0xff);
			SDL_RenderFillRect(renderer_, &cell_rect);
			//render symbol
			tile_renderer_->set_color(cell.r, cell.g, cell.b);
			tile_renderer_->render(
					cell_rect.x,
					cell_rect.y,
					cell.c);
		}

		//update
		SDL_RenderPresent( renderer_ );

	}
}

bool Window::init_sdl()
{
	if( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		printf( "Failure to init SDL! SDL Error: %s\n", SDL_GetError() );
	}
	else
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
	}

	return renderer_ != nullptr;
}
