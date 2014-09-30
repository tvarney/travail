
#ifndef TRAVAIL_LABEL_HPP
#define TRAVAIL_LABEL_HPP

#include "Text.hpp"
#include "Widget.hpp"

namespace travail {
    class Label : public Widget {
    public:
        Label();
        Label(const std::string &str, int attr = 0);
        Label(int x, int y, const std::string &str, int attr = 0);
        Label(const Point2i &pos, const std::string &str, int attr = 0);
        virtual ~Label();
        
        virtual void draw(WINDOW *window);
        
        const Text & getText() const;
        Text & getText();
    protected:
        void genDisplay();
        Text m_Text;
    };
}

#endif
