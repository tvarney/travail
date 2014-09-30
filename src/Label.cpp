
#include "ui/Label.hpp"

#include <cstddef>

using namespace travail;

Label::Label() { }
Label::Label(const std::string &str, int attr) :
    Label(Point2i(), str, attr)
{ }
Label::Label(int x, int y, const std::string &str, int attr) :
    Label(Point2i(x, y), str, attr)
{ }
Label::Label(const Point2i &orig, const std::string &str, int attr) :
    Widget(orig, Dimensions2i(str.size(), 1)), m_Text(str, attr)
{ }
Label::~Label() { }

void Label::draw(WINDOW *window) {
    mvwaddchstr(window, m_Origin.y, m_Origin.x, m_Text.getDisplay().data());
}

const Text & Label::getText() const {
    return m_Text;
}
Text & Label::getText() {
    return m_Text;
}
