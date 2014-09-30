
#ifndef TRAVAIL_CURSOR_HPP
#define TRAVAIL_CURSOR_HPP

#include "Text.hpp"
#include "Widget.hpp"

namespace travail {
    class Cursor {
    public:
        Cursor();
        Cursor(int gap);
        Cursor(const std::string &str, int attr = 0);
        Cursor(int gap, const std::string &str, int attr = 0);
        ~Cursor();
        
        void draw(WINDOW *win, const Widget &widget);
        void erase(WINDOW *win, const Widget &widget);
        void redraw(WINDOW *win, const Widget &old, const Widget &curr);
        
        const Text & getText() const;
        void setText(const std::string &str, int attr);
        void setString(const std::string &str);
        void setAttr(int attr);
        
        int getGap() const;
        void setGap(int gap);
    protected:
        Text m_Text;
        std::basic_string<chtype> m_Erase;
        int m_Gap;
    };
}

#endif
