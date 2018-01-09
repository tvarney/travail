
#ifndef TRAVAIL_UI_COLUMN_HPP
#define TRAVAIL_UI_COLUMN_HPP

#include <cstddef>
#include <vector>
#include "travail/ui/LinearContainer.hpp"

namespace travail {
    /**
     * \brief A Container that lets the user change focus using up/down arrows.
     * 
     * This container does not do any form of layout, it is used simply for
     * focus control.
     * Combined with \c Row objects, this object can define a complicated
     * grid like structure.
     */
    class Column : public LinearContainer {
    public:
        Column();
        virtual ~Column();
        
        virtual int handle(int ch);
    };
}

#endif
