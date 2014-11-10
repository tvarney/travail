
#include "game/Level.hpp"

#include "game/ILevelGenerator.hpp"
#include "graphics/Curses.hpp"
#include "math/Math.hpp"

using namespace travail;

//TODO: Allow for customization of how the tiles are allocated
Level::Level(uint32_t depth, uint32_t width, uint32_t height,
             const std::vector<TileType> &ttypes, const ILevelGenerator &gen) :
    m_allocator(), m_ttypes(ttypes),
    m_dim(clamp(width, 80u, 1024u), clamp(height, 24u, 1024u)), m_center(0,0),
    m_depth(depth), m_tlen(m_dim.width * m_dim.height),
    m_tiles(m_allocator.allocate(m_tlen))
{
    // Pass the tile data to the given generator
    gen.generate(m_depth, m_dim, m_ttypes, m_tiles);
}
Level::Level(uint32_t depth, const Dimensions2u &dim,
             const std::vector<TileType> &ttypes, const ILevelGenerator &gen) :
    Level(depth, dim.width, dim.height, ttypes, gen)
{ }

Level::~Level() {
    if(m_tiles) {
        for(Tile *s = m_tiles, *e = m_tiles + m_tlen; s != e; ++s) {
            m_allocator.destroy(s);
        }
        m_allocator.deallocate(m_tiles, m_tlen);
        m_tiles = nullptr;
    }
}

Tile & Level::get(uint32_t x, uint32_t y) {
    return m_tiles[x + y * m_dim.width];
}
const Tile & Level::get(uint32_t x, uint32_t y) const {
    return m_tiles[x + y * m_dim.width];
}

void Level::render(Window *win, Point2u dest, Point2u src) const {
    render(win, dest, Rectangle2u(src, m_dim));
}
void Level::render(Window *win, Point2u dest, Rectangle2u area) const {
    Dimensions2u wdim(travail::getdim(win));
    area = travail::clip(area, wdim);
    
    wmove(win, dest.y, dest.x);
    uint32_t ymax = area.origin.y + area.dim.height;
    uint32_t xmax = area.origin.x + area.dim.width;
    
    Tile *tptr = m_tiles + area.origin.y * m_dim.width;
    // Counter plus pointer increment
    for(uint32_t y = area.origin.y; y < ymax; ++y, tptr += m_dim.width) {
        for(uint32_t x = area.origin.x; x < xmax; ++x) {
            // Ask the tile to write itself
            tptr[x].write(win, m_ttypes);
        }
    }
}
