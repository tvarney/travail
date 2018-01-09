
#ifndef TRAVAIL_WIDGET_HPP
#define TRAVAIL_WIDGET_HPP

#include "travail/graphics/Curses.hpp"
#include "travail/math/Dimensions.hpp"
#include "travail/math/Point.hpp"

namespace travail {
    class Container;
    
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
        
        virtual void setParent(Container * parent);
        
        virtual Container * getParent();
        virtual const Container * getParent() const;

        virtual void setWindow(WINDOW * window);
        
        virtual WINDOW * getWindow();
        virtual const WINDOW * getWindow() const;
    protected:
        Widget();
        Widget(const Point2i &orig, const Dimensions2i &dim);
        
        Container *m_Parent;
        WINDOW *m_Window;
        Point2i m_Origin;
        Dimensions2i m_Dim;
    };
}

#endif
