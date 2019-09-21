#include "Console.h"
#include "ConsoleCell.h"

Console::Console(unsigned width, unsigned height):  width_(width), height_(height)
{
	cells_ = new ConsoleCell[width_ * height_];
}

Console::~Console()
{
	delete[] cells_;
}

void Console::set_char(unsigned x, unsigned y, char c)
{
	cells_[(y * width_) + x].c = c;
}

void Console::set_color(unsigned x, unsigned y, float r, float g, float b)
{
	cells_[(y * width_) + x].r = r;
	cells_[(y * width_) + x].g = g;
	cells_[(y * width_) + x].b = b;
}

void Console::set_back_color(unsigned x, unsigned y, float r, float g, float b)
{
	cells_[(y * width_) + x].back_r = r;
	cells_[(y * width_) + x].back_g = g;
	cells_[(y * width_) + x].back_b = b;
}

void Console::print(unsigned x, unsigned y,const char* c)
{
	int i = (y * width_) + x;
	while( *c != '\0' && i < (width_ * height_))
	{
		cells_[i++].c = *c++;
	}
}
