#ifndef _H_TTK_CONSOLE
#define _H_TTK_CONSOLE
#include "ConsoleCell.h"
#include <string>
#include <stdexcept>

namespace TTK
{
	class Console
	{
	public:
		Console(unsigned, unsigned);
		//Console() = default;
		~Console();
	
		void clear();
		void set_char(unsigned, unsigned, char);
		void set_back_color(unsigned, unsigned, float, float, float);
		void set_color(unsigned, unsigned, float, float, float);
		void print(unsigned, unsigned,const char*);
		void print(unsigned, unsigned,const std::string&);
	
		unsigned cell_count() const { return width_ * height_; }
		unsigned width() const { return width_; }
		unsigned height() const { return height_; }
		ConsoleCell* cells() const { return cells_; }
	private:
		unsigned width_, height_;

		inline std::size_t index(int x, int y) { return (y * width_) + x; }
	protected:
		ConsoleCell* cells_;
	};
}
#endif //_H_TTK_CONSOLE
