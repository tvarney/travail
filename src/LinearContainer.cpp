
#include "ui/LinearContainer.hpp"

#include <algorithm>

using namespace travail;

LinearContainer::LinearContainer(Window *win) :
    Container(win),
    m_FocusIndex(0)
{ }

LinearContainer::~LinearContainer() { }

void LinearContainer::add(Widget &widget) {
    // Check if the widget is already in the row
    auto iter = std::find(m_Children.begin(), m_Children.end(), &widget);
    if(iter == m_Children.end()) {
        // If not, put it at the end
        m_Children.push_back(&widget);
    }
}
void LinearContainer::remove(Widget &widget) {
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

void LinearContainer::draw() {
    for(Widget *widget : m_Children) {
        widget->draw();
    }
    travail::move(m_Window, getCursor());
}

void LinearContainer::next() {
    if(m_Children.size() <= 1) {
        return;
    }
    m_FocusIndex = ((m_FocusIndex < m_Children.size() - 1) ?
                    (m_FocusIndex + 1) : 0);
    travail::move(m_Window, getCursor());
}

void LinearContainer::prev() {
    if(m_Children.size() <= 1) {
        return;
    }
    m_FocusIndex = ((m_FocusIndex > 0) ? m_FocusIndex : m_Children.size()) - 1;
    travail::move(m_Window, getCursor());
}

Point2i LinearContainer::getCursor() const {
    if(!m_Children.empty()) {
        return getFocused().getCursor();
    }
    return Widget::getCursor();
}

Widget & LinearContainer::getFocused() {
    return *(m_Children[m_FocusIndex]);
}
const Widget & LinearContainer::getFocused() const {
    return *(m_Children[m_FocusIndex]);
}
