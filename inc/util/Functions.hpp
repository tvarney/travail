
#ifndef TRAVAIL_UTIL_FUNCTIONS_HPP
#define TRAVAIL_UTIL_FUNCTIONS_HPP

#include <ncurses.h>
#include "../geom/Dimensions.hpp"
#include "../geom/Point.hpp"

namespace travail {
    void erase(WINDOW *window, const Point2i &origin, int nchars);
    void erase(WINDOW *window, const Point2i &origin, const Dimensions2i &dim);
}

#endif
