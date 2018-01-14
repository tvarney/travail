
#include "travail/ui/Row.hpp"

#include <algorithm>
#include "travail/util/Keys.hpp"

using namespace travail;

const std::string Row::ClassName("Row");

Row::Row() :
    LinearContainer()
{ }

Row::~Row() { }

const std::string & Row::classname() const {
    return Row::ClassName;
}

bool Row::add(Widget * widget) {
    return add(WidgetRef(widget));
}

bool Row::add(WidgetRef widget) {
    if(false == Container::add(widget)) {
        return false;
    }

    // If we added the widget, update our preferred dimensions
    
    Dimensions2i wdim = widget->getPrefDim();
    m_PrefDim.width += wdim.width;
    if(wdim.height > m_PrefDim.height) {
        m_PrefDim.height = wdim.height;
    }
    
    return true;
}

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
