
#ifndef TRAVAIL_MATH_MATH_HPP
#define TRAVAIL_MATH_MATH_HPP

namespace travail {
    template <typename T>
    T min(const T &t1, const T &t2) {
        return (t1 < t2 ? t1 : t2);
    }
    
    template <typename T>
    T max(const T &t1, const T &t2) {
        return (t1 > t2 ? t1 : t2);
    }
    
    template <typename T>
    T clamp(const T &t, const T &min, const T &max) {
        return (t < min ? min : (t > max ? max : t));
    }
}

#endif
