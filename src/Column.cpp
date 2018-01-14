
#include "travail/ui/Column.hpp"

#include <algorithm>
#include "travail/util/Keys.hpp"

using namespace travail;

const std::string Column::ClassName("Column");

Column::Column() :
    LinearContainer()
{ }
Column::Column(const std::string & name) :
    LinearContainer(name)
{ }

Column::~Column() { }

bool Column::add(Widget * widget) {
    return add(WidgetRef(widget));
}

bool Column::add(WidgetRef widget) {
    if(false == Container::add(widget)) {
        return false;
    }
    
    Dimensions2i wdim = widget->getPrefDim();
    m_PrefDim.height += wdim.height;
    if(wdim.width > m_PrefDim.width) {
        m_PrefDim.width = wdim.width;
    }
    
    return true;
}

const std::string & Column::classname() const {
    return Column::ClassName;
}

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
