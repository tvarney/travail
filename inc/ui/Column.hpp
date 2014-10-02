
#ifndef TRAVAIL_UI_COLUMN_HPP
#define TRAVAIL_UI_COLUMN_HPP

#include <cstddef>
#include <vector>
#include "Container.hpp"

namespace travail {
    /**
     * \brief A Container that lets the user change focus using up/down arrows.
     * 
     * This container does not do any form of layout, it is used simply for
     * focus control.
     * Combined with \c Row objects, this object can define a complicated
     * grid like structure.
     */
    class Column : public Container {
    public:
        Column(Window *w = stdscr);
        Column(Point2i &origin, Window *w = stdscr);
        virtual ~Column();
        
        virtual void add(Widget &widget);
        virtual void remove(Widget &widget);
        
        virtual int handle(int ch);
        virtual void draw();
        
        virtual std::size_t getFocusIndex() const;
        virtual Widget & getFocused();
        virtual const Widget & getFocused() const;
    protected:
        std::size_t m_FocusIndex;
        std::vector<Widget *> m_Children;
    };
}

#endif
