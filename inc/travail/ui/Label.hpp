
#ifndef TRAVAIL_LABEL_HPP
#define TRAVAIL_LABEL_HPP

#include "travail/graphics/Text.hpp"
#include "travail/ui/Widget.hpp"

namespace travail {
    class Label : public Widget {
    public:
        static const std::string ClassName;
        
    public:
        Label();
        explicit Label(const std::string & str, int attr = 0);
        Label(const std::string & name, const std::string & str, int attr = 0);
        Label(const Point2i & pos, const std::string & str, int attr = 0);
        Label(const std::string & name, const Point2i & pos,
              const std::string & str, int attr = 0);
        virtual ~Label();
        
        virtual void draw() override;
        
        virtual const std::string & classname() const override;
        
        const Text & getText() const;
        void setText(const std::string &string, int attr = 0);
        void setAttr(int attr);
    protected:
        Text m_Text;
    };
}

#endif
