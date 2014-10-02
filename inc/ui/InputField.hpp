
#ifndef TRAVAIL_UI_INPUT_FIELD_HPP
#define TRAVAIL_UI_INPUT_FIELD_HPP

#include "Label.hpp"
#include "TextField.hpp"

namespace travail {
    class InputField : public TextField {
    public:
        InputField(Window *w = stdscr);
        InputField(int x, int y, const std::string &name, int attr, int width,
                   Window *w = stdscr);
        virtual ~InputField();
        
        virtual void setLabel(const std::string &name, int attr = 0);
        
        virtual void draw();
    protected:
        Label m_Label;
    };
}

#endif
