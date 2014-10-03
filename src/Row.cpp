
#include "ui/Row.hpp"

#include <algorithm>
#include "util/Keys.hpp"

using namespace travail;

Row::Row(Window *win) :
    LinearContainer(win)
{ }

Row::~Row() { }

int Row::handle(int ch) {
    // Check if we are empty, return the character unhandled if so
    if(m_Children.empty()) {
        return ch;
    }
    
    // Allow the currently focused child to handle the character first
    switch(m_Children[m_FocusIndex]->handle(ch)) {
    case travail::cntrl('f'):
    case '\t':
        // Tab, move forwards
        next();
        return 0;
    case travail::cntrl('b'):
    case KEY_BTAB:
        prev();
        return 0;
    }
    return ch;
}
