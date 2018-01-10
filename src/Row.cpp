
#include "travail/ui/Row.hpp"

#include <algorithm>
#include "travail/util/Keys.hpp"

using namespace travail;

Row::Row() :
    LinearContainer()
{ }

Row::~Row() { }

int Row::handle(int ch) {
    // Check if we are empty, return the character unhandled if so
    if(m_Children.empty()) {
        return ch;
    }
    
    // Allow the currently focused child to handle the character first
    switch(m_Children[m_FocusIndex]->handle(ch)) {
    case KEY_ENTER:
    case '\n':
    case '\r':
        return (nextNoWrap() ? 0 : ch);
    case travail::cntrl('f'):
    case '\t':
    case KEY_RIGHT:
        // Tab, move forwards
        next();
        return 0;
    case travail::cntrl('b'):
    case KEY_BTAB:
    case KEY_LEFT:
        prev();
        return 0;
    }
    return ch;
}
