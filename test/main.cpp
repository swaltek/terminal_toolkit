#include "../lib/Window.h"

int main()
{
	Window window(640, 300, "data/art/curses_640x300.bmp");
	if(window.good()) window.run();
	else return -1;

	return 0;
}
