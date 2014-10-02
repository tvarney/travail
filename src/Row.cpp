
#include "ui/Row.hpp"

#include <algorithm>
#include "util/Keys.hpp"

using namespace travail;

Row::Row(Window *win) :
    Container(win),
    m_FocusIndex(0)
{ }

Row::~Row() { }

void Row::add(Widget &widget) {
    // Check if the widget is already in the row
    auto iter = std::find(m_Children.begin(), m_Children.end(), &widget);
    if(iter == m_Children.end()) {
        // If not, put it at the end
        m_Children.push_back(&widget);
    }
}
void Row::remove(Widget &widget) {
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

int Row::handle(int ch) {
    // Check if we are empty, return the character unhandled if so
    if(m_Children.empty()) {
        return ch;
    }
    
    // Allow the currently focused child to handle the character first
    switch(m_Children[m_FocusIndex]->handle(ch)) {
    case travail::cntrl('b'):
    case '\t':
        // Tab, move forwards
        if(m_FocusIndex < m_Children.size()) {
            m_FocusIndex += 1;
            travail::move(m_Window, getFocused().getPos());
            return 0;
        }
        break;
    case travail::cntrl('f'):
    case KEY_BTAB:
        // Back-tab (Shift+Tab), move backwards
        if(m_FocusIndex > 0) {
            m_FocusIndex -= 1;
            travail::move(m_Window, getFocused().getPos());
            return 0;
        }
        break;
    }
    return ch;
}

void Row::draw() {
    for(Widget *widget : m_Children) {
        widget->draw();
    }
}

std::size_t Row::getFocusIndex() const {
    return m_FocusIndex;
}

Widget & Row::getFocused() {
    return *(m_Children[m_FocusIndex]);
}
const Widget & Row::getFocused() const {
    return *(m_Children[m_FocusIndex]);
}
