
#ifndef TRAVAIL_LABEL_HPP
#define TRAVAIL_LABEL_HPP

#include "travail/graphics/Text.hpp"
#include "travail/ui/Widget.hpp"

namespace travail {
    class Label : public Widget {
    public:
        Label();
        Label(const std::string &str, int attr = 0);
        Label(int x, int y, const std::string &str, int attr = 0);
        Label(const Point2i &pos, const std::string &str, int attr = 0);
        virtual ~Label();
        
        virtual void draw();
        
        const Text & getText() const;
        void setText(const std::string &string, int attr = 0);
        void setAttr(int attr);
    protected:
        Text m_Text;
    };
}

#endif
