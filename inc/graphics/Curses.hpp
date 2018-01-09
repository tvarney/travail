
#ifndef TRAVAIL_UTIL_CURSES_HPP
#define TRAVAIL_UTIL_CURSES_HPP

// Turn off macros to avoid macro pollution
// This means that most ncurses functions operating on stdscr implicitly
// are not provided
#ifndef TRAVAIL_ALLOW_NCURSES_MACROS
# define NCURSES_NOMACROS
#endif
#include <ncurses.h>
#include "../math/Dimensions.hpp"
#include "../math/Point.hpp"

namespace travail {
    typedef ::WINDOW Window;
    
    int init_curses();
    
    int wgetch(Window *window, int metadelay = 100);
    
    int init_pair(int fg, int bg);
    
    Dimensions2u getdim(Window *window);
    
    void erase(Window *window, const Point2i &origin, int nchars);
    void erase(Window *window, const Point2i &origin, const Dimensions2i &dim);
    
    void move(Window *window, const Point2i &pos);
    void move(const Point2i &pos);
}

#endif
