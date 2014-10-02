
#ifndef TRAVAIL_UI_ROW_HPP
#define TRAVAIL_UI_ROW_HPP

#include <cstddef>
#include <vector>
#include "Container.hpp"

namespace travail {
    /**
     * \brief A Container that lets the user change focus using tabs
     * 
     * This container does not do any form of layout, it is used simply for
     * focus control.
     */
    class Row : public Container{
    public:
        Row(Window *w = stdscr);
        virtual ~Row();
        
        virtual void add(Widget &widget);
        virtual void remove(Widget &widget);
        
        virtual int handle(int ch);
        virtual void draw();
        
        virtual Point2i getCursor() const;
        
        virtual std::size_t getFocusIndex() const;
        virtual Widget & getFocused();
        virtual const Widget & getFocused() const;
    protected:
        std::size_t m_FocusIndex;
        std::vector<Widget *> m_Children;
    };
}

#endif
