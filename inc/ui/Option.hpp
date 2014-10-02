
#ifndef TRAVAIL_UI_OPTION_HPP
#define TRAVAIL_UI_OPTION_HPP

#include <string>
#include <vector>
#include "Widget.hpp"
#include "Label.hpp"

namespace travail {
    class Option : public Widget {
    public:
        Option(Window *w = stdscr);
        Option(int x, int y, Window *win = stdscr);
        Option(const Point2i &origin, Window *win = stdscr);
        virtual ~Option();
        
        virtual void add(const std::string &optstr);
        virtual void remove(const std::string &optstr);
        
        virtual void setPos(int x, int y);
        virtual void setPos(const Point2i &pos);
        
        virtual bool setChoice(int index);
        virtual int getSelectedAttrib() const;
        virtual void setSelectedAttrib(int attrib);
        virtual int getUnselectedAttrib() const;
        virtual void setUnselectedAttrib(int attrib);
        
        virtual const std::string & getChosenStr() const;
        virtual int getChosenInt() const;
        
        virtual void draw();
        virtual int handle(int ch);
        
        virtual Point2i getCursor() const;
    protected:
        int m_AttrOn, m_AttrOff;
        std::size_t m_Index;
        std::vector<Label> m_Choices;
    };
}

#endif
