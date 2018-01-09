
#include "travail/ui/Label.hpp"

#include <cstddef>

using namespace travail;

Label::Label() :
    Label(Point2i(),"",0)
{ }
Label::Label(const std::string &str, int attr) :
    Label(Point2i(),str,attr)
{ }
Label::Label(int x, int y, const std::string &str, int attr) :
    Label(Point2i(x,y),str, attr)
{ }
Label::Label(const Point2i &pos, const std::string &str, int attr) :
    Widget(pos, Dimensions2i(str.size(), 1)), m_Text(str, attr)
{ }

Label::~Label() { }

void Label::draw() {
    mvwaddchstr(m_Window, m_Origin.y, m_Origin.x, m_Text.getDisplay().data());
}

const Text & Label::getText() const {
    return m_Text;
}
void Label::setText(const std::string &string, int attr) {
    m_Text.set(string, attr);
    draw();
}
void Label::setAttr(int attr) {
    m_Text.setAttr(attr);
    draw();
}
