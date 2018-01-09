
#include "travail/ui/Column.hpp"

#include <algorithm>
#include "travail/util/Keys.hpp"

using namespace travail;

Column::Column(Window *win) :
    LinearContainer(win)
{ }

Column::~Column() { }

int Column::handle(int ch) {
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
    case travail::cntrl('n'):
    case KEY_DOWN:
        // Tab, move forwards
        next();
        break;
    case travail::cntrl('p'):
    case KEY_UP:
        // Back-tab (Shift+Tab), move backwards
        prev();
        break;
    }
    return ch;
}
