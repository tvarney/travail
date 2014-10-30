
#ifndef TRAVAIL_GAME_TILE_HPP
#define TRAVAIL_GAME_TILE_HPP

#include <stdint.h>

namespace travail {
    struct TileType {
        uint32_t glyph;
        uint32_t character;
        uint32_t attributes;
        uint32_t flags;
    };
    
    struct Tile {
        Tile(uint16_t id, uint16_t flags = 0);
        
        uint16_t tileid;
        uint16_t flags;
    };
}

#endif
