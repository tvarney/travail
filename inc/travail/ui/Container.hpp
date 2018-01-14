
#ifndef TRAVAIL_CONTAINER_HPP
#define TRAVAIL_CONTAINER_HPP

#include "travail/ui/Widget.hpp"

#include <vector>

namespace travail {
    typedef std::vector<WidgetRef> ChildList;
    
    class Container : public Widget {
    public:
        virtual ~Container();
        
        virtual void add(Widget * widget);
        virtual void add(WidgetRef widget);
        virtual void remove(Widget * widget);
        virtual void remove(WidgetRef widget);
        
        virtual void setWindow(WINDOW *window);
        
        const ChildList & getChildren() const;
        
        virtual void draw();
    protected:
        Container();
        Container(Point2i &orig, Dimensions2i &dim);
        
        ChildList m_Children;
    };
}

#endif
