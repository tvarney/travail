
#include "ui/Column.hpp"

#include <algorithm>
#include "util/Keys.hpp"

using namespace travail;

Column::Column(Window *win) :
    Container(win),
    m_FocusIndex(0)
{ }

Column::~Column() { }

void Column::add(Widget &widget) {
    // Check if the widget is already in the row
    auto iter = std::find(m_Children.begin(), m_Children.end(), &widget);
    if(iter == m_Children.end()) {
        // If not, put it at the end
        m_Children.push_back(&widget);
    }
}
void Column::remove(Widget &widget) {
    // Check if the widget is in the row
    auto iter = std::find(m_Children.begin(), m_Children.end(), &widget);
    if(iter != m_Children.end()) {
        // If so, get the distance
        std::size_t dist = std::distance(m_Children.begin(), iter);
        // Check if the index of the widget is before our current index
        if(dist < m_FocusIndex) {
            // If so, move our focus back one to compensate
            m_FocusIndex -= 1;
        }
        // Remove child from list of children
        m_Children.erase(iter);
    }
}

int Column::handle(int ch) {
    // Check if we are empty, return the character unhandled if so
    if(m_Children.empty()) {
        return ch;
    }
    
    // Allow the currently focused child to handle the character first
    switch(m_Children[m_FocusIndex]->handle(ch)) {
    case travail::cntrl('n'):
    case KEY_DOWN:
        // Tab, move forwards
        if(m_FocusIndex < m_Children.size() - 1) {
            m_FocusIndex += 1;
            travail::move(getFocused().getCursor());
            return 0;
        }
        break;
    case travail::cntrl('p'):
    case KEY_UP:
        // Back-tab (Shift+Tab), move backwards
        if(m_FocusIndex > 0) {
            m_FocusIndex -= 1;
            travail::move(getFocused().getCursor());
            return 0;
        }
        break;
    }
    return ch;
}

void Column::draw() {
    for(Widget *widget : m_Children) {
        widget->draw();
    }
    travail::move(m_Window, getCursor());
}
Point2i Column::getCursor() const {
    if(!m_Children.empty()) {
        return getFocused().getCursor();
    }
    return Widget::getCursor();
}


std::size_t Column::getFocusIndex() const {
    return m_FocusIndex;
}

Widget & Column::getFocused() {
    return *(m_Children[m_FocusIndex]);
}
const Widget & Column::getFocused() const {
    return *(m_Children[m_FocusIndex]);
}
