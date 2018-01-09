
#include "travail/util/MallocAllocator.hpp"

#include <cstdlib>
#include <stdexcept>
#include <new>

using namespace travail;

MallocAllocator::MallocAllocator() { }
MallocAllocator::~MallocAllocator() { }

void * MallocAllocator::malloc(std::size_t nbytes) {
    void *ptr = std::malloc(nbytes);
    if(ptr == nullptr) {
        throw std::bad_alloc();
    }
    return ptr;
}

void MallocAllocator::free(void *ptr, std::size_t nbytes) {
    std::free(ptr);
}
