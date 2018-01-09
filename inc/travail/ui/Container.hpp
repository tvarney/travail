
#ifndef TRAVAIL_CONTAINER_HPP
#define TRAVAIL_CONTAINER_HPP

#include "travail/ui/Widget.hpp"

#include <memory>
#include <vector>

namespace travail {
    class Container : public Widget {
    public:
        typedef std::vector<std::shared_ptr<Widget>> ChildrenVector;
        
    public:
        virtual ~Container();
        
        virtual void add(Widget * widget);
        virtual void add(std::shared_ptr<Widget> widget);
        virtual void remove(Widget * widget);
        virtual void remove(std::shared_ptr<Widget> widget);
        
        virtual void setWindow(WINDOW *window);
        
        const ChildrenVector & getChildren() const;
        
        virtual void draw();
    protected:
        Container();
        Container(Point2i &orig, Dimensions2i &dim);
        
        ChildrenVector m_Children;
    };
}

#endif
