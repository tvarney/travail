
#ifndef TRAVAIL_TEXT_HPP
#define TRAVAIL_TEXT_HPP

#include <cstddef>
#include <string>

#include "../util/Curses.hpp"

namespace travail {
    class Text {
    public:
        Text();
        Text(const std::string &str, int attr = 0);
        ~Text();
        
        void set(const std::string &str, int attr);
        void setString(const std::string &str);
        void setAttr(int attr);
        
        const std::string & getString() const;
        int getAttr() const;
        const std::basic_string<chtype> & getDisplay() const;
        
        std::size_t size() const;
        
        void draw(Window *win, int x, int y);
    protected:
        void update();
        
        std::string m_Text;
        int m_Attr;
        std::basic_string<chtype> m_Display;
    };
}

#endif
