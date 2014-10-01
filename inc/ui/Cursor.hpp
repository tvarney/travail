
#ifndef TRAVAIL_CURSOR_HPP
#define TRAVAIL_CURSOR_HPP

#include "Label.hpp"

namespace travail {
    class Cursor : public Label {
    public:
        Cursor(WINDOW *win = stdscr);
        Cursor(const std::string &str, WINDOW *win = stdscr);
        Cursor(const std::string &str, int attr, WINDOW *win = stdscr);
        ~Cursor();
        
        void point(const Widget &widget);        
        void move(const Widget &widget);
        void move(const Point2i &neworig);
    };
}

#endif
