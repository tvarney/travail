
#ifndef TRAVAIL_CONTAINER_HPP
#define TRAVAIL_CONTAINER_HPP

#include "Widget.hpp"

namespace travail {
    class Container : public Widget {
    public:
        virtual ~Container();
        
        virtual void add(Widget &widget) = 0;
        virtual void remove(Widget &widget) = 0;
    protected:
        Container();
    };
}

#endif
