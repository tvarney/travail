
#include "travail/ui/Container.hpp"

#include <algorithm>
#include <iostream>

using namespace travail;

Container::Container() :
    Widget()
{ }
Container::Container(Point2i &orig, Dimensions2i &dim) :
    Widget(orig, dim)
{ }
Container::~Container() { }

void Container::add(Widget * widget) {
    add(std::shared_ptr<Widget>(widget));
}

void Container::add(std::shared_ptr<Widget> widget) {
    // We can use the parent attribute of the widget to prevent multiple
    // additions of the same widget
    Container * wparent = widget->getParent();
    if(wparent != this) {
        // If the parent isn't us, and the parent isn't a nullptr, alert the
        // old parent that we are taking ownership of this widget.
        if(wparent != nullptr) {
            wparent->remove(widget);
        }
        // Put the widget on our list of widgets
        m_Children.push_back(widget);
        widget->setParent(this);
    }
}

void Container::remove(Widget * widget) {
    // Hand rolled this to prevent creating a temporary std::shared_ptr
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        if((*iter).get() == widget) {
            m_Children.erase(iter);
            break;
        }
    }
}

void Container::remove(std::shared_ptr<Widget> widget) {
    // Just use std::find()
    auto iter = std::find(m_Children.begin(), m_Children.end(), widget);
    if(iter != m_Children.end()) {
        m_Children.erase(iter);
    }
}

void Container::setWindow(WINDOW *window) {
    m_Window = window;
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        (*iter)->setWindow(window);
    }
}

void Container::draw() {
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        (*iter)->draw();
    }
}

const ChildList & Container::getChildren() const {
    return m_Children;
}
