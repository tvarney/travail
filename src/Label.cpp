
#include "ui/Label.hpp"

#include <cstddef>

using namespace travail;

Label::Label(WINDOW *window) :
    Label(Point2i(),"",0,window)
{ }
Label::Label(const std::string &str, WINDOW *window) :
    Label(Point2i(),str,0,window)
{ }
Label::Label(const std::string &str, int attr, WINDOW *window) :
    Label(Point2i(),str,attr,window)
{ }
Label::Label(int x, int y, const std::string &str, WINDOW *window) :
    Label(Point2i(x,y),str,0,window)
{ }
Label::Label(int x, int y, const std::string &str, int attr, WINDOW *window) :
    Label(Point2i(x,y),str, attr, window)
{ }
Label::Label(const Point2i &pos, const std::string &str, WINDOW *window) :
    Label(pos,str,0,window)
{ }
Label::Label(const Point2i &pos, const std::string &str, int attr,
             WINDOW *window) :
    Widget(pos, Dimensions2i(str.size(), 1), window), m_Text(str, attr)
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
