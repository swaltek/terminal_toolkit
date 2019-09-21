#ifndef _H_CTK_TIMER
#define _H_CTK_TIMER
#include <SDL2/SDL.h>
#include <cstdint>

class Timer
{
	public:
		Timer():
			start_ticks_(0), pause_ticks_(0), paused_(false), started_(false) {}

		void start();
		void stop();
		void pause();
		void unpause();

		uint32_t get_ticks();

		bool is_started() const { return started_; }
		bool is_paused() const { return paused_; }
	private:
		uint32_t start_ticks_;
		uint32_t pause_ticks_;
		bool paused_;
		bool started_;
};
#endif
