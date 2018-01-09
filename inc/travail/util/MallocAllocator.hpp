
#ifndef TRAVAIL_UTIL_MALLOC_ALLOCATOR_HPP
#define TRAVAIL_UTIL_MALLOC_ALLOCATOR_HPP

#include "Allocator.hpp"

namespace travail {
    class MallocAllocator : public Allocator {
    public:
        MallocAllocator();
        virtual ~MallocAllocator();
        
        using Allocator::allocate;
        using Allocator::deallocate;
    protected:
        void * malloc(std::size_t nbytes);
        void free(void *ptr, std::size_t nbytes);
    };
}

#endif
