
#ifndef TRAVAIL_UI_LINEAR_CONTAINER_HPP
#define TRAVAIL_UI_LINEAR_CONTAINER_HPP

#include <cstddef>
#include <vector>
#include "Container.hpp"

namespace travail {
    class LinearContainer : public Container {
    public:
        virtual ~LinearContainer();
        
        virtual void add(Widget &widget);
        virtual void remove(Widget &widget);
        
        virtual void next();
        virtual bool nextNoWrap();
        virtual void prev();
        virtual bool prevNoWrap();
        
        virtual void draw();
        virtual int handle(int ch) = 0;
        
        virtual bool wrap() const;
        virtual void wrap(bool yes);
        
        virtual Point2i getCursor() const;
        
        virtual Widget & getFocused();
        virtual const Widget & getFocused() const;
    protected:
        LinearContainer(Window *w = stdscr);
        
        std::size_t m_FocusIndex;
        std::vector<Widget *> m_Children;
        bool m_Wrap;
    };
}

#endif
