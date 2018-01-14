
#include "travail/ui/Label.hpp"

#include <cstddef>

using namespace travail;

const std::string Label::ClassName("Label");

Label::Label() :
    Label("", Point2i(), "", 0)
{ }

Label::Label(const std::string & str, int attr) :
    Label("", Point2i(), str, attr)
{ }

Label::Label(const std::string & name, const std::string & str, int attr) :
    Label(name, Point2i(), str, attr)
{ }

Label::Label(const Point2i & pos, const std::string & str, int attr) :
    Label("", pos, str, attr)
{ }

Label::Label(const std::string & name, const Point2i & pos,
             const std::string & str, int attr) :
    Widget(name, pos, Dimensions2i(str.size(), 1)),
    m_Text(str, attr)
{ }

Label::~Label() { }

void Label::draw() {
    mvwaddchstr(m_Window, m_Origin.y, m_Origin.x, m_Text.getDisplay().data());
}

const std::string & Label::classname() const {
    return Label::ClassName;
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
