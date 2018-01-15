
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
    
    class Widget {
    public:
        static WidgetRef Null;

        // Default Value 0 results in top left alignment with no expanding
        // 0x00000000 = AlignH_Left | AlignV_Top | ExpandNone
        enum Flags {
            AlignMask   = 0x0000000F,
            AlignH_Mask = 0x00000000,
            AlignV_Mask = 0x00000000,
            ExpandMask  = 0x00000030,
            
            AlignH_Center    = 0x00000002,
            AlignH_Left      = 0x00000000,
            AlignH_Right     = 0x00000001,
            AlignV_Center    = 0x00000008,
            AlignV_Top       = 0x00000000,
            AlignV_Bottom    = 0x00000004,

            AlignCenter      = AlignH_Center | AlignV_Center,
            AlignRight       = AlignH_Right  | AlignV_Center,
            AlignLeft        = AlignH_Left   | AlignV_Center,
            AlignTop         = AlignH_Center | AlignV_Top,
            AlignBottom      = AlignH_Center | AlignV_Bottom,
            AlignTopRight    = AlignH_Right  | AlignV_Top,
            AlignTopLeft     = AlignH_Left   | AlignV_Top,
            AlignBottomLeft  = AlignH_Left   | AlignV_Bottom,
            AlignBottomRight = AlignH_Right  | AlignV_Bottom,
            
            ExpandNone       = 0x00000000,
            ExpandHorizontal = 0x00000010,
            ExpandVertical   = 0x00000020,
            ExpandBoth       = ExpandVertical | ExpandHorizontal,
        };
        
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
        Widget(uint32_t flags = 0);
        Widget(const std::string & name, uint32_t flags = 0);
        Widget(const Point2i & orig, const Dimensions2i & dim,
               uint32_t flags = 0);
        Widget(const std::string & name, const Point2i & orig,
               const Dimensions2i & dim, uint32_t flags = 0);
        
        Container *m_Parent;
        WINDOW *m_Window;
        Point2i m_Origin;
        Dimensions2i m_Dim, m_PrefDim, m_MinDim, m_MaxDim;
        std::string m_Name;
        uint32_t m_Attributes;
    };
}

#endif
