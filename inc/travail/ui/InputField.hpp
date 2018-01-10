
#ifndef TRAVAIL_UI_INPUT_FIELD_HPP
#define TRAVAIL_UI_INPUT_FIELD_HPP

#include "travail/ui/Label.hpp"
#include "travail/ui/TextField.hpp"

namespace travail {
    class InputField : public TextField {
    public:
        InputField();
        InputField(int x, int y, const std::string &name, int attr, int width);
        virtual ~InputField();
        
        virtual void setLabel(const std::string &name, int attr = 0);
        
        virtual void setWindow(WINDOW * window);
        
        virtual void draw();
    protected:
        Label m_Label;
    };
}

#endif
