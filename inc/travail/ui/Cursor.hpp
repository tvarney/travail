
#ifndef TRAVAIL_CURSOR_HPP
#define TRAVAIL_CURSOR_HPP

#include "travail/ui/Label.hpp"

namespace travail {
    class Cursor : public Label {
    public:
        Cursor(Window *win = stdscr);
        Cursor(const std::string &str, Window *win = stdscr);
        Cursor(const std::string &str, int attr, Window *win = stdscr);
        ~Cursor();
        
        void point(const Widget &widget);        
        void move(const Widget &widget);
        void move(const Point2i &neworig);
    };
}

#endif
