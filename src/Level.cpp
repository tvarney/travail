
#include "game/Level.hpp"

#include "graphics/Curses.hpp"
#include "math/Math.hpp"

using namespace travail;

//TODO: Allow for customization of how the tiles are allocated
Level::Level(uint32_t depth, uint32_t width, uint32_t height) :
    m_allocator(),
    m_dim(clamp(width, 80u, 1024u), clamp(height, 24u, 1024u)), m_center(0,0),
    m_depth(depth), m_tlen(m_dim.width * m_dim.height),
    m_tiles(m_allocator.allocate(m_tlen))
{ }
Level::Level(uint32_t depth, const Dimensions2u &dim) :
    Level(depth, dim.width, dim.height)
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
    
}