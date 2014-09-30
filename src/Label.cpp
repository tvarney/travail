
#include "Label.hpp"

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
    Widget(orig, Dimensions2i(str.size(), 1)), m_Text(str), m_Attr(attr)
{
    genDisplay();
}
Label::~Label() { }

void Label::draw(WINDOW *window) {
    mvwaddchstr(window, m_Origin.y, m_Origin.x, m_Display.data());
}

void Label::setAttr(int attr) {
    m_Attr = attr;
    genDisplay();
}

int Label::getAttr() const {
    return m_Attr;
}

void Label::setText(const std::string &text) {
    m_Text = text;
    genDisplay();
}

const std::string & Label::getText() const {
    return m_Text;
}

const CString Label::getDisplay() const {
    return m_Display;
}

void Label::genDisplay() {
    std::size_t length = m_Text.size();
    m_Display.resize(length, static_cast<chtype>(m_Attr));
    for(std::size_t i = 0; i < length; ++i) {
        m_Display[i] |= static_cast<chtype>(m_Text[i]);
    }
}
