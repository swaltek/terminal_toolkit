#include "Console.h"
#include <string>

namespace TTK
{
  Console::Console(unsigned width, unsigned height):  width_(width), height_(height)
  {
    cells_ = new ConsoleCell[width_ * height_];
  }
  
  Console::~Console()
  {
    delete[] cells_;
  }
  
  void Console::clear()
  {
    for(int i{ 0 }; i < cell_count(); ++i)
    {
      cells_[i] = ConsoleCell{};
    }
  }
  
  void Console::set_char(unsigned x, unsigned y, char c)
  {
    auto i = index(x, y);
    cells_[i].c = c;
  }
  
  void Console::set_color(unsigned x, unsigned y, float r, float g, float b)
  {
    auto i = index(x, y);
    cells_[i].r = r;
    cells_[i].g = g;
    cells_[i].b = b;
  }
  
  void Console::set_back_color(unsigned x, unsigned y, float r, float g, float b)
  {
    auto i = index(x, y);
    cells_[i].back_r = r;
    cells_[i].back_g = g;
    cells_[i].back_b = b;
  }
  
  void Console::print(unsigned x, unsigned y,const char* c)
  {
    int i = index(x, y);
    while( *c != '\0' && i < (width_ * height_))
    {
      cells_[i++].c = *c++;
    }
  }
  
  void Console::print(unsigned x, unsigned y,const std::string& str)
  {
    int i = index(x,y);
    for(size_t str_i = 0; str_i < str.length(); ++str_i)
    {
      cells_[i++].c = str.at(str_i);
    }
  }
}
