
#include "travail/ui/LinearContainer.hpp"

#include <algorithm>

using namespace travail;

LinearContainer::LinearContainer() :
    Container(),
    m_FocusIndex(0), m_Wrap(true)
{ }
LinearContainer::LinearContainer(const std::string & name) :
    Container(name),
    m_FocusIndex(0), m_Wrap(true)
{ }

LinearContainer::~LinearContainer() { }

void LinearContainer::draw() {
    Container::draw();
    travail::move(m_Window, getCursor());
}

bool LinearContainer::wrap() const {
    return m_Wrap;
}

void LinearContainer::wrap(bool yes) {
    m_Wrap = yes;
}

void LinearContainer::next() {
    if(m_Children.size() <= 1) {
        return;
    }
    m_FocusIndex = ((m_FocusIndex < m_Children.size() - 1) ?
                    (m_FocusIndex + 1) : (m_Wrap ? 0 : m_FocusIndex));
    travail::move(m_Window, getCursor());
}

bool LinearContainer::nextNoWrap() {
    if(m_FocusIndex < m_Children.size() - 1) {
        m_FocusIndex += 1;
        travail::move(m_Window, getCursor());
        return true;
    }
    return false;
}

void LinearContainer::prev() {
    if(m_Children.size() <= 1) {
        return;
    }
    m_FocusIndex = ((m_FocusIndex > 0) ? (m_FocusIndex - 1) :
                    (m_Wrap ? m_Children.size() - 1 : m_FocusIndex));
    travail::move(m_Window, getCursor());
}

bool LinearContainer::prevNoWrap() {
    if(m_FocusIndex > 0) {
        m_FocusIndex -= 1;
        travail::move(m_Window, getCursor());
        return true;
    }
    return false;
}

Point2i LinearContainer::getCursor() const {
    if(!m_Children.empty()) {
        return getFocused()->getCursor();
    }
    return Widget::getCursor();
}

WidgetRef & LinearContainer::getFocused() {
    if(m_Children.empty()) {
        return Widget::Null;
    }
    return m_Children[m_FocusIndex];
}
const WidgetRef & LinearContainer::getFocused() const {
    if(m_Children.empty()) {
        return Widget::Null;
    }
    return m_Children[m_FocusIndex];
}

std::size_t LinearContainer::getFocusedIndex() const {
    return m_FocusIndex;
}
