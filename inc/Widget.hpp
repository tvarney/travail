
#ifndef TRAVAIL_WIDGET_HPP
#define TRAVAIL_WIDGET_HPP

#include <ncurses.h>
#include "Dimensions.hpp"
#include "Point.hpp"

namespace travail {
    class Widget {
    public:
        virtual ~Widget();
        
        virtual int handle(int ch);
        virtual void draw(WINDOW *window) = 0;
        
        virtual const Dimensions2i & getDim() const;
        
        virtual const Point2i & getPos() const;
        virtual void setPos(const Point2i &pos);
        virtual void setPos(int x, int y);
        
        virtual void center(WINDOW *window);
        virtual void center_h(WINDOW *window);
        virtual void center_v(WINDOW *window);
    protected:
        Widget();
        Widget(const Point2i &orig, const Dimensions2i &dim);
        
        Point2i m_Origin;
        Dimensions2i m_Dim;
    };
}

#endif
