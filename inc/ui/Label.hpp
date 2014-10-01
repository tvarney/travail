
#ifndef TRAVAIL_LABEL_HPP
#define TRAVAIL_LABEL_HPP

#include "Text.hpp"
#include "Widget.hpp"

namespace travail {
    class Label : public Widget {
    public:
        Label(WINDOW *window = stdscr);
        Label(const std::string &str, WINDOW *win = stdscr);
        Label(const std::string &str, int attr, WINDOW *win = stdscr);
        Label(int x, int y, const std::string &str, WINDOW *win = stdscr);
        Label(int x, int y, const std::string &str, int attr,
              WINDOW *win = stdscr);
        Label(const Point2i &pos, const std::string &str,
              WINDOW *win = stdscr);
        Label(const Point2i &pos, const std::string &str, int attr,
              WINDOW *win = stdscr);
        virtual ~Label();
        
        virtual void draw();
        virtual void erase();
        
        const Text & getText() const;
        void setText(const std::string &string, int attr = 0);
    protected:
        Text m_Text;
    };
}

#endif
