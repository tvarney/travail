
#ifndef TRAVAIL_UTIL_ALLOCATOR_HPP
#define TRAVAIL_UTIL_ALLOCATOR_HPP

#include <cstddef>
#include <stdint.h>

namespace travail {
    class Allocator {
    public:
        virtual ~Allocator();
        
        template <typename T>
        T * allocate(std::size_t nitems) {
            return reinterpret_cast<T *>(malloc(nitems * sizeof(T)));
        }
        template <typename T>
        void deallocate(T *ptr, std::size_t nitems) {
            free(reinterpret_cast<void *>(ptr), nitems * sizeof(T));
        }
    protected:
        virtual void * malloc(std::size_t nbytes) = 0;
        virtual void free(void *ptr, std::size_t nbytes) = 0;
        
        Allocator();
    };
}

#endif
