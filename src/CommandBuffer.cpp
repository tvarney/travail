
#include "ui/CommandBuffer.hpp"

#include <cctype>

using namespace travail;

CommandBuffer::CommandBuffer(Window *win) :
    CommandBuffer(Point2i(0, getmaxy(stdscr) - 1), 79, win)
{ }
CommandBuffer::CommandBuffer(int width, Window *win) :
    CommandBuffer(Point2i(0, getmaxy(stdscr) - 1), width, win)
{ }
CommandBuffer::CommandBuffer(int x, int y, int width, Window *win) :
    CommandBuffer(Point2i(x,y), width, win)
{ }
CommandBuffer::CommandBuffer(const Point2i &origin, int width, Window *win) :
    TextField(origin, width, win),
    m_HistoryIndex(0), m_MaxHistorySize(1000), m_History(),
    m_HistPos(m_History.end())
{ }
CommandBuffer::~CommandBuffer() { }

int CommandBuffer::handle(int ch) {
    /*
    if((ch = TextField::handle(ch)) == 0) {
        if(m_HistoryIndex > 0) {
            // Editing a history item
            m_HistoryIndex = 0; //< Mark that we are now not in history
        }
        return 0;
    }
    
    switch(ch) {
    case KEY_UP:
        // Check if we have history
        if(m_History.size() > 0) {
            if(m_HistoryIndex == 0) {
                // We are not currently looking through history
                m_HistoryIndex = 1;
                m_HistPos = m_History.begin();
                m_Stash = m_Buffer; // Save our current line
                setContents(*m_HistPos);
            }else if(m_HistoryIndex <= m_MaxHistorySize) {
                if(m_HistoryIndex + 1 <= m_MaxHistorySize) {
                    m_HistoryIndex += 1;
                    m_HistPos++;
                    setContents(*m_HistPos);
                }
            }
        }
        return 0; //< Return indicator that we handled KEY_UP
    case KEY_DOWN:
        if(m_History.size() > 0) {
            if(m_HistoryIndex == 1) {
                m_HistoryIndex = 0;
                setContents(m_Stash);
            }else if(m_HistoryIndex > 1) {
                m_HistPos--;
                m_HistoryIndex -= 1;
                setContents(*m_HistPos);
            }
            break;
        }
        return 0;
    }
    return ch;
    */
    return TextField::handle(ch);
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

