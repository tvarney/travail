
#include "travail/ui/Container.hpp"

#include <algorithm>
#include <iostream>

using namespace travail;

Container::Container() :
    Widget()
{ }
Container::Container(const std::string & name) :
    Widget(name)
{ }
Container::Container(const Point2i & orig, const Dimensions2i & dim) :
    Widget(orig, dim)
{ }
Container::Container(const std::string & name, const Point2i & orig,
                     const Dimensions2i & dim) :
    Widget(name, orig, dim)
{ }
Container::~Container() { }

bool Container::add(Widget * widget) {
    return add(std::shared_ptr<Widget>(widget));
}

bool Container::add(WidgetRef widget) {
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
        return true;
    }
    return false;
}

bool Container::remove(Widget * widget) {
    // Hand rolled this to prevent creating a temporary std::shared_ptr
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        if((*iter).get() == widget) {
            m_Children.erase(iter);
            return true;
        }
    }
    return false;
}

bool Container::remove(WidgetRef widget) {
    // Just use std::find()
    auto iter = std::find(m_Children.begin(), m_Children.end(), widget);
    if(iter != m_Children.end()) {
        m_Children.erase(iter);
        return true;
    }
    return false;
}

void Container::setWindow(WINDOW * window) {
    m_Window = window;
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        (*iter)->setWindow(window);
    }
}

const ChildList & Container::getChildren() const {
    return m_Children;
}

WidgetRef Container::findByName(const std::string & name) {
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        if((*iter)->name() == name) {
            return *iter;
        }
        WidgetRef ref = (*iter)->findByName(name);
        if(ref != Widget::Null) {
            return ref;
        }
    }
    return Widget::Null;
}

const WidgetRef Container::findByName(const std::string & name) const {
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        if((*iter)->name() == name) {
            return *iter;
        }
        WidgetRef ref = (*iter)->findByName(name);
        if(ref != Widget::Null) {
            return ref;
        }
    }
    return Widget::Null;
}

void Container::draw() {
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        (*iter)->draw();
    }
}
