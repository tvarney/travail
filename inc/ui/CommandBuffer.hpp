
#ifndef TRAVAIL_COMMAND_BUFFER_HPP
#define TRAVAIL_COMMAND_BUFFER_HPP

#include <list>
#include <string>

#include <ncurses.h>

#include "../geom/Point.hpp"

namespace travail {
    class CommandBuffer {
    public:
        CommandBuffer();
        ~CommandBuffer();
        
        int handle(WINDOW *win, int ch);
        void draw(WINDOW *win);
        void setPos(int y);
        void setRecall(std::size_t recall);
        
        void addToHistory(const std::string &string);
        void clear();
        
        const std::string & data() const;
    protected:
        Point2i m_Origin;
        int m_ScreenStart, m_ScreenPos;
        std::size_t m_Index, m_HistoryIndex, m_MaxHistorySize;
        std::string m_Buffer;
        std::list<std::string> m_History;
        std::string m_Stash;
    };
}

#endif
