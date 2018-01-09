
#include "travail/ui/Cursor.hpp"

#include "travail/graphics/Curses.hpp"

using namespace travail;

Cursor::Cursor() :
    Cursor("->", A_BOLD)
{ }
Cursor::Cursor(const std::string &str, int attr) :
    Label(str, attr)
{ }
Cursor::~Cursor() { }

void Cursor::point(const Widget &widget) {
    m_Origin.y = widget.getPos().y;
    m_Origin.x = widget.getPos().x - (m_Dim.width + 1);
    draw();
}

void Cursor::move(const Widget &widget) {
    travail::erase(m_Window, m_Origin, m_Dim.width);
    point(widget);
}

void Cursor::move(const Point2i &neworig) {
    travail::erase(m_Window, m_Origin, m_Dim.width);
    m_Origin = neworig;
    draw();
}


