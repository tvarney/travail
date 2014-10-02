
#include "ui/TextField.hpp"

#include <cctype>
#include "util/Keys.hpp"

using namespace travail;

TextField::TextField(Window *win) :
    TextField(Point2i(0,0), 79, win)
{ }
TextField::TextField(int width, Window *win) :
    TextField(Point2i(0,0), width, win)
{ }
TextField::TextField(int x, int y, int width, Window *win) :
    TextField(Point2i(x,y), width, win)
{ }
TextField::TextField(const Point2i &origin, int width, Window *win) :
    Widget(origin, Dimensions2i((width > 2 ? width : 2), 1), win),
    m_StrIndex(0), m_DispIndex(0), m_Cursor(0), m_Advance(m_Dim.width / 2)
{
    m_Buffer.reserve(width);
}
TextField::~TextField() { }

const std::string & TextField::getContents() const {
    return m_Buffer;
}
void TextField::setContents(const std::string &string) {
    m_Buffer = string;
    m_StrIndex = m_Cursor = m_DispIndex = 0;
    this->toeol();
}

int TextField::handle(int ch) {
    if(std::isprint(ch)) {
        this->addch(ch);
        return 0;
    }
    
    switch(ch) {
    case KEY_DC:
        this->delch();
        break;
    case 127:
    case KEY_BACKSPACE:
        this->bspace();
        break;
    case KEY_LEFT:
        this->cursleft();
        break;
    case KEY_RIGHT:
        this->cursright();
        break;
    case KEY_HOME:
        this->tosol();
        break;
    case KEY_END:
        this->toeol();
        break;
    case travail::cntrl('a'):
        this->tosol();
        break;
    case travail::cntrl('e'):
        this->toeol();
        break;
    case travail::cntrl('b'):
        this->cursleft();
        break;
    case travail::meta('b'):
        this->pword();
        break;
    case travail::cntrl('f'):
        this->cursright();
        break;
    case travail::meta('f'):
        this->nword();
        break;
    case travail::cntrl('k'):
        this->cleareol();
        break;
    default:
        return ch;
    }
    return 0;
}

void TextField::draw() {
    int nchars = (static_cast<int>(m_Buffer.size()) - m_DispIndex);
    nchars = ((nchars > m_Dim.width) ? m_Dim.width : nchars);
    // Write string to display
    mvwaddnstr(m_Window, m_Origin.y, m_Origin.x, m_Buffer.data() + m_DispIndex,
               nchars);
}

void TextField::addch(char ch) {
    if(m_StrIndex == m_Buffer.size()) {
        m_Buffer.append(1, ch); //< Append character
        m_Cursor += 1; //< Increment screen cursor
        m_StrIndex += 1; //< Increment string index
        
        if(m_Cursor >= m_Dim.width) { //< We went over our allocated dim
            m_DispIndex += m_Advance; //< Advance the display index
            m_Cursor -= m_Advance; //< move our cursor back
            draw(); //< Draw ourself
            // Erase characters at end of line
            travail::erase(m_Window,
                           Point2i(m_Origin.x + m_Cursor, m_Origin.y),
                           m_Dim.width - m_Cursor);
            updateCurs();
        }else {
            mvwaddch(m_Window, m_Origin.y, m_Origin.x + m_Cursor - 1, ch);
        }
    }else {
        m_Buffer.insert(m_StrIndex, 1, ch);
        m_Cursor += 1;
        m_StrIndex += 1;
        if(m_Cursor >= m_Dim.width) {
            m_DispIndex += m_Advance;
            m_Cursor -= m_Advance;
        }
        
        travail::erase(m_Window, m_Origin, m_Dim.width);
        draw();
    }
}
void TextField::delch() {
    bspace();
}
void TextField::bspace() {
    if(m_Buffer.size() == 0) {
        return; //< Ignore backspace if buffer is empty
    }
    
    // Check if we are at end of buffer
    if(m_StrIndex == m_Buffer.size()) {
        // Remove last character
        m_Buffer.pop_back();
        // Overwrite it on screen
        mvwaddch(m_Window, m_Origin.y, m_Origin.x + m_Cursor - 1, ' ');
        m_Cursor -= 1;
        m_StrIndex -= 1;
        if(m_Cursor == 0 && m_StrIndex > 0) {
            m_Cursor += m_Advance;
            m_DispIndex = ((m_DispIndex >= m_Advance) ?
                           (m_DispIndex - m_Advance) : 0);
            draw();
        }else {
            mvwaddch(m_Window, m_Origin.y, m_Origin.x + m_Cursor, ' ');
            wmove(m_Window, m_Origin.y, m_Origin.x + m_Cursor);
        }
    }else if(m_StrIndex > 0) {
        m_Buffer.erase(m_StrIndex - 1, 1);
        
        m_StrIndex -= 1;
        m_Cursor -= 1;
        if(m_Cursor == 0 && m_StrIndex > 0) {
            m_Cursor += m_Advance;
            m_DispIndex = ((m_DispIndex >= m_Advance) ?
                           (m_DispIndex - m_Advance) : 0);
        }
        
        travail::erase(m_Window, m_Origin, m_Dim.width);
        draw();
    }
}
void TextField::cursleft() {
    if(m_Cursor > 0 && m_StrIndex > 0) {
        m_Cursor -= 1;
        m_StrIndex -= 1;
        if(m_Cursor == 0 && m_StrIndex > 0) {
            m_Cursor += m_Advance;
            m_DispIndex = ((m_DispIndex >= m_Advance) ?
                           (m_DispIndex - m_Advance) : 0);
            travail::erase(m_Window, m_Origin, m_Dim.width);
            draw();
        }
        updateCurs();
    }
}
void TextField::cursright() {
    if(m_StrIndex != m_Buffer.size()) {
        m_Cursor += 1; //< Increment screen cursor
        m_StrIndex += 1; //< Increment string index
        
        if(m_Cursor >= m_Dim.width) { //< We went over our allocated dim
            m_DispIndex += m_Advance; //< Advance the display index
            m_Cursor -= m_Advance; //< move our cursor back
            travail::erase(m_Window, m_Origin, m_Dim.width);
            draw();
        }
        updateCurs();
    }
}
void TextField::pword() { }
void TextField::nword() { }
void TextField::toeol() {
    m_DispIndex = m_Cursor = 0;
    m_StrIndex = m_Buffer.size();
    if(m_StrIndex > m_Dim.width) {
        m_Cursor = m_Dim.width - 1;
        m_DispIndex = m_StrIndex - m_Dim.width;
    }else {
        m_Cursor = m_StrIndex;
    }
    draw();
}
void TextField::tosol() {
    m_DispIndex = m_Cursor = m_StrIndex = 0;
    draw();
}

void TextField::cleareol() { }

void TextField::clear() {
    m_Buffer.clear();
    m_StrIndex = m_DispIndex = m_Cursor = 0;
    travail::erase(m_Window, m_Origin, m_Dim.width);
    updateCurs();
}

void TextField::updateCurs() const {
    wmove(m_Window, m_Origin.y, m_Origin.x + m_Cursor);
}
