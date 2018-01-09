
#ifndef TRAVAIL_CURSOR_HPP
#define TRAVAIL_CURSOR_HPP

#include "travail/ui/Label.hpp"

namespace travail {
    class Cursor : public Label {
    public:
        Cursor();
        Cursor(const std::string &str, int attr = 0);
        ~Cursor();
        
        void point(const Widget &widget);        
        void move(const Widget &widget);
        void move(const Point2i &neworig);
    };
}

#endif
