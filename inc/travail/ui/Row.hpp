
#ifndef TRAVAIL_UI_ROW_HPP
#define TRAVAIL_UI_ROW_HPP

#include <cstddef>
#include <vector>
#include "LinearContainer.hpp"

namespace travail {
    /**
     * \brief A Container that lets the user change focus using tabs
     * 
     * This container does not do any form of layout, it is used simply for
     * focus control.
     */
    class Row : public LinearContainer {
    public:
        Row();
        virtual ~Row();
        
        virtual int handle(int ch);
    };
}

#endif
