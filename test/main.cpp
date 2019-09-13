#include "../lib/TileRenderer.h"

#include <SDL2/SDL.h>
#include <cstdio>
const unsigned WINDOW_WIDTH{ 640 };
const unsigned WINDOW_HEIGHT{ 300 };

SDL_Window* window{ nullptr };
SDL_Renderer* renderer{ nullptr };

bool init()
{
	if( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		printf( "Failure to init SDL! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		window = SDL_CreateWindow( "RL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == nullptr )
		{
			printf( "Failure to create window! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == nullptr )
			{
				printf( "Failure to create renderer! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0xff, 0xff, 0xff, 0xff );
			}
		}
	}

	return renderer != nullptr;
}

void close()
{
	SDL_DestroyWindow( window );
	window = nullptr;
	SDL_DestroyRenderer( renderer );
	renderer = nullptr;

	SDL_Quit();
}

int main()
{
	if( init() != true )
	{
		printf( "Could not init game!" );
		close();
		return -1;
	}

	bool quit{ false };

	//init code
	TileRenderer tile( renderer , "data/art/curses_640x300.bmp");

	while( quit != true )
	{
		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT) quit = true;
			else if( e.type == SDL_KEYDOWN )
			{
				//handle input code
				switch( e.key.keysym.sym )
				{
				}
			}
		}

		//update code
		
		//display code
		//clear screen
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xff );
		SDL_RenderClear( renderer );

		//render code
		tile.render(1, 1, 'a');

		//update screen
		SDL_RenderPresent( renderer );
	}

	close();
	return 0;
}
