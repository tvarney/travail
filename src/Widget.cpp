
#include "ui/Widget.hpp"

using namespace travail;

Widget::Widget() { }
Widget::Widget(const Point2i &orig, const Dimensions2i &dim) :
    m_Origin(orig), m_Dim(dim)
{ }
Widget::~Widget() { }

int Widget::handle(int ch) {
    return ch;
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

void Widget::center(int width, int height) {
    m_Origin.x = (width - m_Dim.width) >> 1;
    m_Origin.y = (height - m_Dim.height) >> 1;
}
void Widget::center_h(int width) {
    m_Origin.x = (width - m_Dim.width) >> 1;
}
void Widget::center_v(int height) {
    m_Origin.y = (height - m_Dim.height) >> 1;
}
