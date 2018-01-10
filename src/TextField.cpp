
#include "travail/ui/TextField.hpp"

#include <cctype>
#include <limits>
#include <stdint.h>

#include "travail/util/Keys.hpp"

using namespace travail;

static int _word_boundary(int ch) {
    return (std::isspace(ch) || !(std::isalnum(ch)));
}

TextField::TextField() :
    TextField(Point2i(0,0), 79)
{ }
TextField::TextField(int width) :
    TextField(Point2i(0,0), width)
{ }
TextField::TextField(int x, int y, int width) :
    TextField(Point2i(x,y), width)
{ }
TextField::TextField(const Point2i &origin, int width) :
    Widget(origin, Dimensions2i((width > 2 ? width : 2), 1)),
    m_ValidCh(nullptr), m_MaxStrSize(std::numeric_limits<std::size_t>::max()),
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
    travail::erase(m_Window, Point2i(m_Origin.x + m_Cursor, m_Origin.y),
                   m_Dim.width - m_Cursor);
}

void TextField::setMaxLength(std::size_t max) {
    m_MaxStrSize = max;
}
std::size_t TextField::getMaxLength() const {
    return m_MaxStrSize;
}

void TextField::setPredicate(TextField::TextPredicate validch) {
    m_ValidCh = validch;
}

Point2i TextField::getCursor() const {
    return Point2i(m_Origin.x + m_Cursor, m_Origin.y);
}

int TextField::handle(int ch) {
    if(ch < 127 && ch > 31) {
        this->addch(ch);
        return 0;
    }
    
    switch(ch) {
    case travail::cntrl('d'):
    case KEY_DC:
        this->delch();
        break;
    case 127:
    case KEY_BACKSPACE:
        this->bspace();
        break;
    case travail::cntrl('b'):
    case KEY_LEFT:
        if(m_StrIndex == 0) {
            return ch;
        }
        this->cmove(-1);
        break;
    case travail::cntrl('f'):
    case KEY_RIGHT:
        if(m_StrIndex == m_Buffer.size()) {
            return ch;
        }
        this->cmove(1);
        break;
    case travail::cntrl('a'):
    case KEY_HOME:
        this->tosol();
        break;
    case travail::cntrl('e'):
    case KEY_END:
        this->toeol();
        break;
    case travail::meta('b'):
        this->pword();
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
    if((m_ValidCh != nullptr && !(m_ValidCh(ch))) ||
       m_StrIndex >= m_MaxStrSize)
    {
        return;
    }
    
    if(m_StrIndex == m_Buffer.size()) {
        m_Buffer.append(1, ch); //< Append character
        m_Cursor += 1; //< Increment screen cursor
        m_StrIndex += 1; //< Increment string index
        
        if(m_Cursor >= static_cast<uint32_t>(m_Dim.width) &&
           m_StrIndex != m_MaxStrSize)
        {
            // We went over our allocated dim
            m_DispIndex += m_Advance; //< Advance the display index
            m_Cursor -= m_Advance; //< move our cursor back
            draw(); //< Draw ourself
            // Erase characters at end of line
            travail::erase(m_Window,
                           Point2i(m_Origin.x + m_Cursor, m_Origin.y),
                           m_Dim.width - m_Cursor);
        }else {
            mvwaddch(m_Window, m_Origin.y, m_Origin.x + m_Cursor - 1, ch);
        }
        updateCurs();
    }else {
        m_Buffer.insert(m_StrIndex, 1, ch);
        m_Cursor += 1;
        m_StrIndex += 1;
        if(m_Cursor >= static_cast<uint32_t>(m_Dim.width)) {
            m_DispIndex += m_Advance;
            m_Cursor -= m_Advance;
        }
        
        travail::erase(m_Window, m_Origin, m_Dim.width);
        draw();
        updateCurs();
    }
}
void TextField::delch() {
    if(m_StrIndex == m_Buffer.size()) {
        return;
    }
    
    m_Buffer.erase(m_StrIndex, 1); //< Erase character we are on
    
    if(m_StrIndex == m_Buffer.size()) {
        mvwaddch(m_Window, m_Origin.y, m_Origin.x + m_Cursor, ' ');
        updateCurs();
    }else {
        int nchars = static_cast<int>(m_Buffer.size() - m_StrIndex);
        if(static_cast<std::size_t>(nchars) > m_Dim.width - m_Cursor) {
            nchars = m_Dim.width - m_Cursor;
            mvwaddnstr(m_Window, m_Origin.y, m_Origin.x + m_Cursor,
                       m_Buffer.data() + m_DispIndex + m_Cursor, nchars);
        }else {
            mvwaddnstr(m_Window, m_Origin.y, m_Origin.x + m_Cursor,
                       m_Buffer.data() + m_DispIndex + m_Cursor, nchars);
            waddch(m_Window, ' ');
        }
        updateCurs();
    }
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
            updateCurs();
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
        updateCurs();
    }
}

void TextField::cmove(int amount) {
    int temp;
    if(amount > 0) {
        if(m_StrIndex != m_Buffer.size()) {
            // Clamp amount we are moving so we stay in the buffer
            amount = ((m_StrIndex + amount > m_Buffer.size()) ?
                      (m_Buffer.size() - m_StrIndex) : amount);
            
            // Update our buffer index
            m_StrIndex += amount;
            
            // Check if this would cause us to run off the end of the display
            // area
            temp = amount + m_Cursor;
            if(temp >= m_Dim.width) {
                // Get the amount to move our display index to leave just
                // m_Amount of characters before the cursor
                m_DispIndex = m_StrIndex - m_Advance;
                m_Cursor = m_Advance;
                
                // Erase ourself
                erase();
                draw();
                updateCurs();
            }else {
                // Update our cursor position
                m_Cursor = temp;
                updateCurs();
            }
        }
    }else if(amount < 0) {
        if(m_StrIndex != 0) {
            // Clamp abs(amount) so we stay in the buffer
            amount = ((static_cast<std::size_t>(-amount) > m_StrIndex) ?
                      m_StrIndex : -amount);
            m_StrIndex -= amount;
            
            temp = m_Cursor - amount;
            if(temp <= 0) {
                // Get the amount to move our display index such that we leave
                // m_Advance characters after the cursor
                if((m_Dim.width - m_Advance) > m_StrIndex) {
                    // We can't move the display index back m_Advance
                    m_DispIndex = 0;
                    m_Cursor = m_StrIndex;
                }else {
                    m_Cursor = m_Dim.width - m_Advance;
                    m_DispIndex = m_StrIndex - m_Cursor;
                }
                // redraw
                erase();
                draw();
                updateCurs();
            }else {
                // Update our cursor position
                m_Cursor = temp;
                updateCurs();
            }
        }
    }
}

void TextField::pword() {
    // Can't move to previous word if we are at the start of the buffer
    if(m_StrIndex == 0) {
        return;
    }
    
    std::size_t pos = m_StrIndex - 1;
    while(pos > 0 && _word_boundary(m_Buffer[pos])) { pos -= 1; }
    while(pos > 1 && !(_word_boundary(m_Buffer[pos - 1]))) { pos -= 1; }
    if(!(_word_boundary(m_Buffer[pos - 1]))) {
        pos -= 1;
    }
    
    cmove(-(static_cast<int>(m_StrIndex - pos)));
}
void TextField::nword() {
    std::size_t blen = m_Buffer.size();
    if(m_StrIndex == blen) {
        return;
    }
    std::size_t pos = m_StrIndex + 1;
    while(pos < blen && _word_boundary(m_Buffer[pos])) { pos += 1; }
    while(pos < blen && !(_word_boundary(m_Buffer[pos]))) { pos += 1; }
    cmove(static_cast<int>(pos - m_StrIndex));
}
void TextField::toeol() {
    m_DispIndex = m_Cursor = 0;
    m_StrIndex = m_Buffer.size();
    if(m_StrIndex > static_cast<uint32_t>(m_Dim.width)) {
        m_Cursor = m_Dim.width - 1;
        m_DispIndex = m_StrIndex - m_Dim.width;
    }else {
        m_Cursor = m_StrIndex;
    }
    draw();
    updateCurs();
}
void TextField::tosol() {
    m_DispIndex = m_Cursor = m_StrIndex = 0;
    draw();
    updateCurs();
}

void TextField::cleareol() {
    if(m_StrIndex != m_Buffer.size()) {
        // Erase string content
        m_Buffer.erase(m_StrIndex, m_Buffer.size() - m_StrIndex);
        
        // Clear to end of display
        travail::erase(m_Window, Point2i(m_Origin.x + m_Cursor, m_Origin.y),
                       m_Dim.width - m_Cursor);
        updateCurs();
    }
}

void TextField::clear() {
    m_Buffer.clear();
    m_StrIndex = m_DispIndex = m_Cursor = 0;
    travail::erase(m_Window, m_Origin, m_Dim.width);
    updateCurs();
}

void TextField::updateCurs() const {
    wmove(m_Window, m_Origin.y, m_Origin.x + m_Cursor);
}
