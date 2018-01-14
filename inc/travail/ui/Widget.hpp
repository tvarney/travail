
#ifndef TRAVAIL_WIDGET_HPP
#define TRAVAIL_WIDGET_HPP

#include <memory>
#include <string>

#include "travail/graphics/Curses.hpp"
#include "travail/math/Dimensions.hpp"
#include "travail/math/Point.hpp"

namespace travail {
    class Container;
    class Widget;

    typedef std::shared_ptr<Widget> WidgetRef;
    
    enum Align {
        Mask    = 0x0000000F,
        
        Center      = 0x00000000,
        Right       = 0x00000001,
        Left        = 0x00000002,
        Top         = 0x00000003,
        Bottom      = 0x00000004,
        TopRight    = 0x00000005,
        TopLeft     = 0x00000006,
        BottomLeft  = 0x00000007,
        BottomRight = 0x00000008,
    };
    
    enum Expand {
        Mask       = 0x00000030,
        Horizontal = 0x00000010,
        Vertical   = 0x00000020,
        Both = Vertical | Horizontal,
    };
    
    class Widget {
    public:
        static WidgetRef Null;
        
    public:
        virtual ~Widget();
        
        virtual int handle(int ch);
        virtual void draw() = 0;
        virtual void erase();
        
        virtual void setDim(const Dimensions2i & dim);
        virtual const Dimensions2i & getDim() const;

        virtual void setMaxDim(const Dimensions2i & dim);
        virtual const Dimensions2i & getMaxDim() const;

        virtual void setMinDim(const Dimensions2i & dim);
        virtual const Dimensions2i & getMinDim() const;

        virtual void setPrefDim(const Dimensions2i & dim);
        virtual const Dimensions2i & getPrefDim() const;
        
        virtual const Point2i & getPos() const;
        virtual void setPos(const Point2i & pos);
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

        virtual WidgetRef findByName(const std::string & name);
        virtual const WidgetRef findByName(const std::string & name) const;
        
        virtual const std::string & classname() const = 0;
        virtual const std::string & name() const;
    protected:
        Widget();
        Widget(const std::string & name);
        Widget(const Point2i & orig, const Dimensions2i & dim);
        Widget(const std::string & name, const Point2i & orig,
               const Dimensions2i & dim);
        
        Container *m_Parent;
        WINDOW *m_Window;
        Point2i m_Origin;
        Dimensions2i m_Dim, m_PrefDim, m_MinDim, m_MaxDim;
        std::string m_Name;
        uint32_t m_Attributes;
    };
}

#endif
