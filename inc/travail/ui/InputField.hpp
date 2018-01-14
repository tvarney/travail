
#ifndef TRAVAIL_UI_INPUT_FIELD_HPP
#define TRAVAIL_UI_INPUT_FIELD_HPP

#include "travail/ui/Label.hpp"
#include "travail/ui/TextField.hpp"

namespace travail {
    class InputField : public TextField {
    public:
        static const std::string ClassName;
        
    public:
        InputField();
        explicit InputField(const std::string & name);
        InputField(int x, int y, const std::string & label, int attr,
                   int width);
        InputField(const std::string & name, int x, int y,
                   const std::string & label, int attr, int width);
        virtual ~InputField();
        
        virtual void setLabel(const std::string & label, int attr = 0);
        
        virtual void setWindow(WINDOW * window) override;

        virtual const std::string & classname() const override;
        
        virtual void draw() override;
    protected:
        Label m_Label;
    };
}

#endif
