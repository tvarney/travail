
#ifndef TRAVAIL_UI_OPTION_HPP
#define TRAVAIL_UI_OPTION_HPP

#include <string>
#include <vector>
#include "travail/ui/Label.hpp"
#include "travail/ui/Orientation.hpp"
#include "travail/ui/Widget.hpp"

namespace travail {
    class Option : public Widget {
    public:
        Option();
        Option(Orientation o);
        Option(int x, int y);
        Option(Orientation o,int x, int y); 
        Option(const Point2i &origin);
        Option(Orientation o, const Point2i &orig);
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
        Orientation m_Orient;
        int m_AttrOn, m_AttrOff;
        std::size_t m_Index;
        std::vector<Label> m_Choices;
    };
}

#endif
