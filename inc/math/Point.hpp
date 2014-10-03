
#ifndef TRAVAIL_POINT_HPP
#define TRAVAIL_POINT_HPP

namespace travail {
    template <typename Type>
    class Point {
    public:
        Point() :
            x(0), y(0)
        { }
        Point(Type x, Type y) :
            x(x), y(y)
        { }
        Point(const Point<Type> &source) :
            x(source.x), y(source.y)
        { }
        template <typename Other>
        Point(const Point<Other> &source) :
            x(source.x), y(source.y)
        { }
        ~Point() { }
        
        Point<Type> & operator=(const Point<Type> &rhs) {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        template <typename Other>
        Point<Type> & operator=(const Point<Other> &rhs) {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
        
        Type x, y;
    };
    
    typedef Point<int> Point2i;
}

#endif
