
#ifndef TRAVAIL_COMMAND_BUFFER_HPP
#define TRAVAIL_COMMAND_BUFFER_HPP

#include <list>
#include <string>

#include "TextField.hpp"
#include "../math/Point.hpp"
#include "../util/Curses.hpp"
#include "../util/History.hpp"

namespace travail {
    class CommandBuffer : public TextField {
    public:
        CommandBuffer(Window *win = stdscr);
        CommandBuffer(int width, Window *win = stdscr);
        CommandBuffer(int x, int y, int width, Window *win = stdscr);
        CommandBuffer(const Point2i &origin, int width, Window *win = stdscr);
        virtual ~CommandBuffer();
        
        int handle(int ch);
        
        History & getHistory();
        const History & getHistory() const;
    protected:
        int m_HistoryIndex;
        History m_History;
        History::Iterator m_HistoryPos;
        std::string m_Stash;
    };
}

#endif
