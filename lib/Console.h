#ifndef _H_CTK_CONSOLE
#define _H_CTK_CONSOLE
#include "ConsoleCell.h"
#include "Window.h"

class Console
{
	friend class Window;

public:
	Console(unsigned, unsigned);
	~Console();

	void set_char(unsigned, unsigned, char);
	void set_back_color(unsigned, unsigned, float, float, float);
	void set_color(unsigned, unsigned, float, float, float);
	void print(unsigned, unsigned,const char*);

	unsigned width() const { return width_; }
	unsigned height() const { return height_; }
private:
	unsigned width_, height_;
protected:
	ConsoleCell* cells_;

};
#endif
