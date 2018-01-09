
#ifndef TRAVAIL_CONTAINER_HPP
#define TRAVAIL_CONTAINER_HPP

#include "travail/ui/Widget.hpp"

namespace travail {
    class Container : public Widget {
    public:
        virtual ~Container();
        
        virtual void add(Widget &widget) = 0;
        virtual void remove(Widget &widget) = 0;
    protected:
        Container(Window *w);
        Container(Point2i &orig, Dimensions2i &dim, Window *w);
    };
}

#endif
