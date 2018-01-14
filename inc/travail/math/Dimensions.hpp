
#ifndef TRAVAIL_DIMENSIONS_HPP
#define TRAVAIL_DIMENSIONS_HPP

#include <stdint.h>
#include <limits>

namespace travail {
    template <typename Type>
    class Dimensions {
    public:
        static Dimensions<Type> Max() {
            return Dimensions<Type>(
                std::numeric_limits<Type>::max(),
                std::numeric_limits<Type>::max());
        }
        static Dimensions<Type> Min() {
            return Dimensions<Type>(
                std::numeric_limits<Type>::lowest(),
                std::numeric_limits<Type>::lowest());
        }
        
    public:
        Dimensions() :
            width(0), height(0)
        { }
        Dimensions(Type width, Type height) :
            width(width), height(height)
        { }
        Dimensions(const Dimensions<Type> &source) :
            width(source.width), height(source.height)
        { }
        template <typename Other>
        Dimensions(const Dimensions<Other> &source) :
            width(source.width), height(source.height)
        { }
        ~Dimensions() { }
        
        Dimensions<Type> & operator=(const Dimensions<Type> &rhs) {
            width = rhs.width;
            height = rhs.height;
            return *this;
        }
        template <typename Other>
        Dimensions<Type> & operator=(const Dimensions<Other> &rhs) {
            width = rhs.width;
            height = rhs.height;
            return *this;
        }
        
        Type width, height;
    };
    
    typedef Dimensions<int32_t> Dimensions2i;
    typedef Dimensions<uint32_t> Dimensions2u;
}

#endif
