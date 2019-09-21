#include "Timer.h"
#include <SDL2/SDL.h>
#include <cstdint>

void Timer::start()
{
	started_ = true;
	paused_ = false;
	start_ticks_ = SDL_GetTicks();
	pause_ticks_ = 0;
}

void Timer::stop()
{
	started_ = false;
	paused_ = false;
	start_ticks_ = 0;
	pause_ticks_ = 0;
}

void Timer::pause()
{
	if( started_ )
	{
		paused_ = true;
		start_ticks_ = 0;
		pause_ticks_ = SDL_GetTicks() - start_ticks_;
	}
}

void Timer::unpause()
{
	if( paused_  )
	{
		paused_ = false;
		start_ticks_ = SDL_GetTicks() - pause_ticks_;
		pause_ticks_ = 0;
	}
}

uint32_t Timer::get_ticks()
{
	if( started_ )
	{
		if( paused_ ) return pause_ticks_;
		else return SDL_GetTicks() - start_ticks_;
	}
	return 0;
}
