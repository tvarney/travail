
#include "travail/ui/InputField.hpp"

using namespace travail;

InputField::InputField() :
    InputField(0, 0, "Input:", A_UNDERLINE, 10)
{ }
InputField::InputField(int x, int y, const std::string &name, int attr,
                       int width) :
    TextField(x + name.size() + 1,y,width),
    m_Label(x,y,name,attr)
{ }

InputField::~InputField() { }

void InputField::setLabel(const std::string &name, int attr) {
    m_Label.setText(name, attr);
}

void InputField::setWindow(WINDOW * window) {
    Widget::setWindow(window);
    m_Label.setWindow(window);
}

void InputField::draw() {
    m_Label.draw();
    TextField::draw();
}
