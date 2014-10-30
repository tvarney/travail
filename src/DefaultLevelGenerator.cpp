
#include "game/DefaultLevelGenerator.hpp"

#include "game/Tile.hpp"

using namespace travail;

DefaultLevelGenerator::DefaultLevelGenerator(uint16_t w, uint16_t f,
                                             uint16_t u, uint16_t d) :
    m_wallid(w), m_floorid(f), m_upstairid(u), m_downstairid(d)
{ }
DefaultLevelGenerator::~DefaultLevelGenerator() { }

void DefaultLevelGenerator::generate(uint32_t depth, const Dimensions2u &dim,
                                     const std::vector<TileType> &ttype,
                                     Tile *tiles) const
{
    for(uint32_t i = 0; i < dim.width; ++i) {
        new (tiles + i) Tile(m_wallid);
    }
    for(uint32_t r = 1, off=dim.width; r < dim.height-1; ++r,off+=dim.width) {
        new (tiles + off) Tile(m_wallid);
        for(uint32_t c = 1; c < dim.width - 1; ++c) {
            new (tiles + off + c) Tile(m_floorid);
        }
        new (tiles + off + dim.width - 1) Tile(m_wallid);
    }
    Tile *tptr = tiles + (dim.width * (dim.height - 2));
    for(uint32_t i = 0; i < dim.width; ++i) {
        new (tptr + i) Tile(m_wallid);
    }
    
    tiles[dim.width + 1].tileid = m_upstairid;
    tiles[dim.height * dim.width - 2].tileid = m_downstairid;
}
