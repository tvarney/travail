
#include "ui/Text.hpp"

using namespace travail;

Text::Text() { }
Text::Text(const std::string &str, int attr) :
    m_Text(str), m_Attr(attr)
{
    update();
}
Text::~Text() { }

void Text::set(const std::string &str, int attr) {
    m_Text = str;
    m_Attr = attr;
    update();
}
void Text::setString(const std::string &str) {
    m_Text = str;
    update();
}
void Text::setAttr(int attr) {
    m_Attr = attr;
    update();
}

const std::string & Text::getString() const {
    return m_Text;
}
int Text::getAttr() const {
    return m_Attr;
}
const std::basic_string<chtype> & Text::getDisplay() const {
    return m_Display;
}

std::size_t Text::size() const {
    return m_Text.size();
}

void Text::draw(WINDOW *win, int x, int y) {
    mvwaddchstr(win, y, x, m_Display.data());
}

void Text::update() {
    std::size_t length = m_Text.size();
    m_Display.clear();
    m_Display.resize(length, static_cast<chtype>(m_Attr));
    for(std::size_t i = 0; i < length; ++i) {
        m_Display[i] |= static_cast<chtype>(m_Text[i]);
    }
}
