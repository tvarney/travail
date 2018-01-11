
#ifndef TRAVAIL_UI_LINEAR_CONTAINER_HPP
#define TRAVAIL_UI_LINEAR_CONTAINER_HPP

#include <stdint.h>
#include <cstddef>
#include <vector>
#include "travail/ui/Container.hpp"

namespace travail {
    class LinearContainer : public Container {
    public:
        virtual ~LinearContainer();
        
        virtual void next();
        virtual bool nextNoWrap();
        virtual void prev();
        virtual bool prevNoWrap();
        
        virtual void draw();
        virtual int handle(int ch) = 0;
        
        virtual bool wrap() const;
        virtual void wrap(bool yes);
        
        virtual Point2i getCursor() const;
        
        virtual std::shared_ptr<Widget> & getFocused();
        virtual const std::shared_ptr<Widget> & getFocused() const;

        virtual std::size_t getFocusedIndex() const;
    protected:
        LinearContainer();
        
        std::size_t m_FocusIndex;
        bool m_Wrap;
    };
}

#endif