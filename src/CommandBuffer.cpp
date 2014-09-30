
#include "ui/CommandBuffer.hpp"

#include <cctype>

using namespace travail;

CommandBuffer::CommandBuffer() :
    m_Origin(0,0), m_ScreenStart(0), m_ScreenPos(0),
    m_Index(0), m_HistoryIndex(1), m_MaxHistorySize(1000)
{ }
CommandBuffer::~CommandBuffer() { }

int CommandBuffer::handle(WINDOW *win, int ch) {
    if(std::isprint(ch)) {
        /* Add to buffer */
        if(m_Index == m_Buffer.size()) {
            m_Buffer += static_cast<char>(ch);
        }else {
            m_Buffer.insert(m_Index, 1, static_cast<char>(ch));
        }
        draw(win);
        return 0;
    }else {
        switch(ch) {
        default:
            return ch;
        }
    }
}

void CommandBuffer::draw(WINDOW *win) {
    /* Draw visible portion */
    mvwaddnstr(stdscr, m_Origin.y, 0, m_Buffer.data()+m_ScreenStart,
               m_Buffer.size() - m_ScreenStart);
}

void CommandBuffer::setPos(int y) {
    m_Origin.y = y;
}

void CommandBuffer::setRecall(std::size_t recall) {
    if(recall < m_MaxHistorySize) {
        std::size_t diff = m_MaxHistorySize - recall;
        while(m_History.size() > recall) {
            m_History.erase(m_History.begin());
        }
        m_HistoryIndex -= diff;
    }
    m_MaxHistorySize = recall;
}

void CommandBuffer::addToHistory(const std::string &string) {
    m_History.push_back(string);
    if(m_History.size() > m_MaxHistorySize) {
        m_History.erase(m_History.begin());
    }else {
        m_HistoryIndex += 1;
    }
}
void CommandBuffer::clear() {
    m_Buffer.clear();
}

const std::string & CommandBuffer::data() const {
    return m_Buffer;
}
