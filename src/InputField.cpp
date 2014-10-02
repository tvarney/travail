
#include "ui/InputField.hpp"

using namespace travail;

InputField::InputField(Window *w) :
    InputField(0, 0, "Input:", A_UNDERLINE, 10, w)
{ }
InputField::InputField(int x, int y, const std::string &name, int attr,
                       int width, Window *w) :
    TextField(x + name.size() + 1,y,width,w),
    m_Label(x,y,name,attr)
{ }

InputField::~InputField() { }

void InputField::setLabel(const std::string &name, int attr) {
    m_Label.setText(name, attr);
}

void InputField::draw() {
    m_Label.draw();
    TextField::draw();
}
