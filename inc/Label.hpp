
#ifndef TRAVAIL_LABEL_HPP
#define TRAVAIL_LABEL_HPP

#include <string>
#include "Widget.hpp"

namespace travail {
    typedef std::basic_string<chtype> CString;
    
    class Label : public Widget {
    public:
        Label();
        Label(const std::string &str, int attr = 0);
        Label(int x, int y, const std::string &str, int attr = 0);
        Label(const Point2i &pos, const std::string &str, int attr = 0);
        virtual ~Label();
        
        virtual void draw(WINDOW *window);
        
        virtual void setAttr(int attr);
        virtual int getAttr() const;
        
        virtual void setText(const std::string &text);
        virtual const std::string & getText() const;
        
        virtual const CString getDisplay() const;
    protected:
        void genDisplay();
        
        std::string m_Text;
        int m_Attr;
        CString m_Display;
    };
}

#endif
