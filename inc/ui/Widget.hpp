
#ifndef TRAVAIL_WIDGET_HPP
#define TRAVAIL_WIDGET_HPP

#include <ncurses.h>
#include "../geom/Dimensions.hpp"
#include "../geom/Point.hpp"

namespace travail {
    class Widget {
    public:
        virtual ~Widget();
        
        virtual int handle(int ch);
        virtual void draw() = 0;
        
        virtual void setDim(const Dimensions2i &dim);
        virtual const Dimensions2i & getDim() const;
        
        virtual const Point2i & getPos() const;
        virtual void setPos(const Point2i &pos);
        virtual void setPos(int x, int y);
        
        virtual void center(int width, int height);
        virtual void center_h(int width);
        virtual void center_v(int height);
        
        virtual WINDOW * getWindow();
        virtual const WINDOW * getWindow() const;
    protected:
        Widget(WINDOW *window = stdscr);
        Widget(const Point2i &orig, const Dimensions2i &dim,
               WINDOW *window = stdscr);
        
        WINDOW *m_Window;
        Point2i m_Origin;
        Dimensions2i m_Dim;
    };
}

#endif
