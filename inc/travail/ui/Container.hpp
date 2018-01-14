
#ifndef TRAVAIL_CONTAINER_HPP
#define TRAVAIL_CONTAINER_HPP

#include "travail/ui/Widget.hpp"

#include <vector>

namespace travail {
    typedef std::vector<WidgetRef> ChildList;
    
    class Container : public Widget {
    public:
        virtual ~Container();
        
        virtual bool add(Widget * widget);
        virtual bool add(WidgetRef widget);
        virtual bool remove(Widget * widget);
        virtual bool remove(WidgetRef widget);
        
        virtual void setWindow(WINDOW * window);
        
        const ChildList & getChildren() const;
        
        virtual WidgetRef findByName(const std::string & name) override;
        virtual const WidgetRef findByName(const std::string & name) const
            override;
        
        virtual void draw();
    protected:
        Container();
        Container(const std::string & name);
        Container(const Point2i & orig, const Dimensions2i & dim);
        Container(const std::string & name, const Point2i & orig,
                  const Dimensions2i & dim);
        
        ChildList m_Children;
    };
}

#endif
