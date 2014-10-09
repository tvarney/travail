
#include "ui/Widget.hpp"

using namespace travail;

Widget::Widget(WINDOW *window) :
    m_Window(window)
{ }
Widget::Widget(const Point2i &orig, const Dimensions2i &dim, WINDOW *window) :
    m_Window(window), m_Origin(orig), m_Dim(dim)
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

WINDOW * Widget::getWindow() {
    return m_Window;
}
const WINDOW * Widget::getWindow() const {
    return m_Window;
}
