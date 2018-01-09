
#ifndef TRAVAIL_MATH_RECTANGLE_HPP
#define TRAVAIL_MATH_RECTANGLE_HPP

#include <stdint.h>

#include "Dimensions.hpp"
#include "Point.hpp"

namespace travail {
    template <typename Scalar>
    struct Rectangle {
        Rectangle() :
            origin(), dim()
        { }
        Rectangle(const Scalar &x, const Scalar &y,
                  const Scalar &width, const Scalar &height) :
            origin(x,y), dim(width, height)
        { }
        Rectangle(const Point<Scalar> &o, const Dimensions<Scalar> &d) :
            origin(o), dim(d)
        { }
        Rectangle(const Rectangle<Scalar> &source) :
            origin(source.origin), dim(source.dim)
        { }
        template <typename T>
        Rectangle(const Rectangle<T> &source) :
            origin(source.origin), dim(source.dim)
        { }
        ~Rectangle() { }
        
        const Scalar & x1() const {
            return origin.x;
        }
        const Scalar & x2() const {
            return origin.x + dim.width;
        }
        const Scalar & y1() const {
            return origin.y;
        }
        const Scalar & y2() const {
            return origin.y + dim.width;
        }
        
        Point<Scalar> origin;
        Dimensions<Scalar> dim;
    };
    
    template <typename T>
    Rectangle<T> clip(const Rectangle<T> &src, const Rectangle<T> &dest) {
        Rectangle<T> r(src);
        T diff;
        // Move x1 into the destination, clipping width
        if(src.x1() > dest.x2()) {
            r.origin.x = dest.x2();
            r.dim.width = T(0);
        }else if(src.x1() < dest.x1()) {
            r.origin.x = dest.x1();
            diff = dest.x1() - src.x1();
            r.dim.width = (diff > src.dim.width ? 0 : diff);
        }
        
        // Move y1 into the destination, clipping height
        if(src.y1() > dest.y2()) {
            r.origin.y = dest.y2();
            r.dim.height = T(0);
        }else if(src.y1() < dest.y1()) {
            diff = dest.y1() - src.y1();
            r.dim.height = (diff > src.dim.height ? 0 : diff);
        }
        
        return r;
    }
    template <typename T>
    Rectangle<T> clip(const Rectangle<T> &src, const Dimensions<T> &dim) {
        return Rectangle<T>(src.origin,
                            Dimensions<T>(((src.dim.width > dim.width) ?
                                           dim.width : src.dim.width),
                                          ((src.dim.height > dim.height) ?
                                           dim.height : src.dim.height)));
    }
    
    typedef Rectangle<int32_t> Rectangle2i;
    typedef Rectangle<uint32_t> Rectangle2u;
}

#endif
