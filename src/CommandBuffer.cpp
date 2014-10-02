
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
    m_HistoryIndex(-1)
{ }
CommandBuffer::~CommandBuffer() { }

int CommandBuffer::handle(int ch) {
    if((ch = TextField::handle(ch)) == 0) {
        if(m_HistoryIndex >= 0) {
            // Editing a history item
            m_HistoryIndex = -1; //< Mark that we are now not in history
        }
        return 0;
    }
    
    switch(ch) {
    case KEY_UP:
        // Check if we have history
        if(m_History.size() > 0) {
            if(m_HistoryIndex < 0) {
                // We are not currently looking through history
                m_HistoryIndex = 0;
                
                m_HistoryPos = m_History.begin();
                m_Stash = m_Buffer; // Save our current line
                setContents(*m_HistoryPos); // Copy history to buffer
            }else if(m_HistoryIndex + 1 < m_History.size()) {
                m_HistoryIndex += 1;
                m_HistoryPos++;
                setContents(*m_HistoryPos);
            }
        }
        return 0; //< Return indicator that we handled KEY_UP
    case KEY_DOWN:
        if(m_History.size() > 0) {
            if(m_HistoryIndex == 0) {
                m_HistoryIndex = -1;
                setContents(m_Stash);
            }else if(m_HistoryIndex > 0) {
                m_HistoryPos--;
                m_HistoryIndex -= 1;
                setContents(*m_HistoryPos);
            }
        }
        return 0;
    }
    return ch;
}

History & CommandBuffer::getHistory() {
    return m_History;
}
const History & CommandBuffer::getHistory() const {
    return m_History;
}
