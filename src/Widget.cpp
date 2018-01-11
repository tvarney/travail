
#include "travail/ui/Widget.hpp"

#include "travail/ui/Container.hpp"

#ifndef NDEBUG
# include <iostream>
#endif

using namespace travail;

Widget::Widget() :
    m_Parent(nullptr), m_Window(nullptr)
{ }
Widget::Widget(const Point2i &orig, const Dimensions2i &dim) :
    m_Parent(nullptr), m_Window(nullptr), m_Origin(orig), m_Dim(dim)
{ }
Widget::~Widget() { }

int Widget::handle(int ch) {
    return ch;
}
void Widget::erase() {
    travail::erase(m_Window, m_Origin, m_Dim);
}

void Widget::setDim(const Dimensions2i &dim) {
    m_Dim = dim;
}
const Dimensions2i & Widget::getDim() const {
    return m_Dim;
}

const Point2i & Widget::getPos() const {
    return m_Origin;
}

void Widget::setPos(const Point2i &pos) {
    m_Origin = pos;
}
void Widget::setPos(int x, int y) {
    m_Origin = Point2i(x, y);
}

Point2i Widget::getCursor() const {
    int x, y;
    getbegyx(m_Window, y,x);
    return Point2i(m_Origin.x + x, m_Origin.y + y);
}

void Widget::center(int width, int height) {
    int x = (width - m_Dim.width) >> 1;
    int y = (height - m_Dim.height) >> 1;
    setPos(x, y);
}
void Widget::center_h(int width) {
    int x = (width - m_Dim.width) >> 1;
    setPos(x, getPos().y);
}
void Widget::center_v(int height) {
    int y = (height - m_Dim.height) >> 1;
    setPos(getPos().x, y);
}

void Widget::setParent(Container * parent) {
    m_Parent = parent;
    setWindow(parent != nullptr ? parent->getWindow() : nullptr);
}

Container * Widget::getParent() {
    return m_Parent;
}

const Container * Widget::getParent() const {
    return m_Parent;
}

void Widget::setWindow(WINDOW * window) {
    m_Window = window;
}

WINDOW * Widget::getWindow() {
    return m_Window;
}
const WINDOW * Widget::getWindow() const {
    return m_Window;
}
