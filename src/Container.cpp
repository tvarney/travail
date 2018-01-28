
#include "travail/ui/Container.hpp"

#include <algorithm>
#include <iostream>

using namespace travail;

Container::Container() :
    Widget(), m_CanFocus(false)
{ }
Container::Container(const std::string & name) :
    Widget(name), m_CanFocus(false)
{ }
Container::Container(const Point2i & orig, const Dimensions2i & dim) :
    Widget(orig, dim), m_CanFocus(false)
{ }
Container::Container(const std::string & name, const Point2i & orig,
                     const Dimensions2i & dim) :
    Widget(name, orig, dim), m_CanFocus(false)
{ }
Container::~Container() { }

int Container::handle(int key) {
    if(m_FocusedChild != nullptr) {
        return m_FocusedChild->handle(key);
    }
    return key;
}

bool Container::canFocus() const {
    return m_CanFocus;
}

bool Container::canFocusDynamic() const {
    for(auto it = m_Children.begin(); it != m_Children.end(); ++it) {
        if((*it)->canFocus()) {
            return true;
        }
    }
    return false;
}

void Container::notifyFocusable(Widget * child, bool focusable) {
    bool old_focus = m_CanFocus;
    if(focusable) {
        m_CanFocus = true;
    }else {
        m_CanFocus = canFocusDynamic();
    }
    if(m_Parent != nullptr && m_CanFocus != old_focus) {
        m_Parent->notifyFocusable(this, m_CanFocus);
    }
}

bool Container::setFocus(Widget * widget) {
    if(m_CanFocus && widget->getParent() == this && widget->canFocus()) {
        m_FocusedChild = widget;
        return true;
    }
    return false;
}

bool Container::setFocus(WidgetRef widget) {
    return setFocus(widget.get());
}

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
        bool old_focus = m_CanFocus;
        m_CanFocus |= widget->canFocus();
        if(old_focus != m_CanFocus) {
            if(m_Parent != nullptr) {
                m_Parent->notifyFocusable(this, m_CanFocus);
            }
        }
        return true;
    }
    return false;
}

bool Container::remove(Widget * widget) {
    // Hand rolled this to prevent creating a temporary std::shared_ptr
    for(auto iter = m_Children.begin(); iter != m_Children.end(); ++iter) {
        if((*iter).get() == widget) {
            if(m_FocusedChild == widget) {
                findNextFocusable(iter);
            }
            m_Children.erase(iter);
            

            // If the child is focusable, we need to make sure there is another
            // focusable child in our children list. If there isn't we need to
            // notify our parent container that we are no longer focusable.
            if((*iter)->canFocus()) {
                bool old_focus = m_CanFocus;
                m_CanFocus = this->canFocusDynamic();
                if(m_CanFocus != old_focus) {
                    if(m_Parent != nullptr) {
                        m_Parent->notifyFocusable(this, m_CanFocus);
                    }
                }
            }
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

void Container::findNextFocusable(ChildList::iterator it) {
    ChildList::iterator iter = it;
    iter++;
    while(iter != m_Children.end()) {
        if((*iter)->canFocus()) {
            m_FocusedChild = (*iter).get();
            return;
        }
        iter++;
    }
    for(iter = m_Children.begin(); iter != it; ++iter) {
        if((*iter)->canFocus()) {
            m_FocusedChild = (*iter).get();
            return;
        }
    }
}
