
#ifndef TRAVAIL_COMMAND_BUFFER_HPP
#define TRAVAIL_COMMAND_BUFFER_HPP

#include <list>
#include <string>

#include "TextField.hpp"

#include "../geom/Point.hpp"
#include "../util/Curses.hpp"

namespace travail {
    class CommandBuffer : public TextField {
    public:
        CommandBuffer(Window *win = stdscr);
        CommandBuffer(int width, Window *win = stdscr);
        CommandBuffer(int x, int y, int width, Window *win = stdscr);
        CommandBuffer(const Point2i &origin, int width, Window *win = stdscr);
        virtual ~CommandBuffer();
        
        int handle(int ch);
        
        void setRecall(std::size_t recall);
        
        void addToHistory(const std::string &string);
    protected:
        std::size_t m_HistoryIndex, m_MaxHistorySize;
        std::list<std::string> m_History;
        std::list<std::string>::iterator m_HistPos;
        std::string m_Stash;
    };
}

#endif
