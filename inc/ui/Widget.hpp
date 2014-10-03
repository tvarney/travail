
#ifndef TRAVAIL_WIDGET_HPP
#define TRAVAIL_WIDGET_HPP

#include "../util/Curses.hpp"
//#include <ncurses.h>
#include "../math/Dimensions.hpp"
#include "../math/Point.hpp"

namespace travail {
    class Widget {
    public:
        virtual ~Widget();
        
        virtual int handle(int ch);
        virtual void draw() = 0;
        virtual void erase();
        
        virtual void setDim(const Dimensions2i &dim);
        virtual const Dimensions2i & getDim() const;
        
        virtual const Point2i & getPos() const;
        virtual void setPos(const Point2i &pos);
        virtual void setPos(int x, int y);
        
        virtual Point2i getCursor() const;
        
        virtual void center(int width, int height);
        virtual void center_h(int width);
        virtual void center_v(int height);
        
        virtual Window * getWindow();
        virtual const Window * getWindow() const;
    protected:
        Widget(Window *window = stdscr);
        Widget(const Point2i &orig, const Dimensions2i &dim,
               Window *window = stdscr);
        
        Window *m_Window;
        Point2i m_Origin;
        Dimensions2i m_Dim;
    };
}

#endif
