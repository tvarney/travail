
#include "travail/ui/InputField.hpp"

using namespace travail;

const std::string InputField::ClassName("InputField");

InputField::InputField() :
    InputField("", 0, 0, "Input:", A_UNDERLINE, 10)
{ }
InputField::InputField(int x, int y, const std::string & label, int attr,
                       int width) :
    InputField("", x, y, label, attr, width)
{ }
InputField::InputField(const std::string & name, int x, int y,
                       const std::string & label, int attr, int width) :
    TextField(name, x + label.size() + 1, y, width),
    m_Label(Point2i(x, y), label, attr)
{ }

InputField::~InputField() { }

void InputField::setLabel(const std::string & label, int attr) {
    m_Label.setText(label, attr);
}

void InputField::setWindow(WINDOW * window) {
    Widget::setWindow(window);
    m_Label.setWindow(window);
}

const std::string & InputField::classname() const {
    return InputField::ClassName;
}

void InputField::draw() {
    m_Label.draw();
    TextField::draw();
}
