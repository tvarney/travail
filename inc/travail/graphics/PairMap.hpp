
#ifndef TRAVAIL_GRAPHICS_PAIR_MAP_HPP
#define TRAVAIL_GRAPHICS_PAIR_MAP_HPP

#include <map>
#include <stdint.h>

namespace travail {
    class PairMap {
    public:
        PairMap();
        ~PairMap();
        
        int32_t get(int16_t fg, int16_t bg);
    protected:
        int32_t m_current;
        std::map<uint32_t, int32_t> m_map;
    };
}

#endif
