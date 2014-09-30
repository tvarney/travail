
#include "Cursor.hpp"

using namespace travail;

Cursor::Cursor() :
    Cursor(1, "->", A_BOLD)
{ }
Cursor::Cursor(int gap) :
    Cursor(gap, "->", A_BOLD)
{ }
Cursor::Cursor(const std::string &str, int attr) :
    Cursor(1, str, attr)
{ }
Cursor::Cursor(int gap, const std::string &str, int attr) :
    m_Text(str, attr), m_Erase(str.size(), ' '), m_Gap(gap)
{ }
Cursor::~Cursor() { }

void Cursor::draw(WINDOW *win, const Widget &widget) {
    Point2i pos = widget.getPos();
    pos.x -= (m_Gap + static_cast<int>(m_Text.size()));
    m_Text.draw(win, pos.x, pos.y);
}
void Cursor::erase(WINDOW *win, const Widget &widget) {
    Point2i pos = widget.getPos();
    pos.x -= (m_Gap + static_cast<int>(m_Text.size()));
    mvwaddchstr(win, pos.y, pos.x, m_Erase.data());
}
void Cursor::redraw(WINDOW *win, const Widget &old, const Widget &curr) {
    erase(win, old);
    draw(win, curr);
}

const Text & Cursor::getText() const {
    return m_Text;
}
void Cursor::setText(const std::string &str, int attr) {
    m_Text.set(str, attr);
    m_Erase.resize(str.size(), ' ');
}
void Cursor::setString(const std::string &str) {
    m_Text.setString(str);
    m_Erase.resize(str.size(), ' ');
}
void Cursor::setAttr(int attr) {
    m_Text.setAttr(attr);
}

int Cursor::getGap() const {
    return m_Gap;
}

void Cursor::setGap(int gap) {
    m_Gap = gap;
}
