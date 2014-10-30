
#ifndef TRAVAIL_GAME_LEVEL_HPP
#define TRAVAIL_GAME_LEVEL_HPP

#include <memory>
#include <vector>

#include "Tile.hpp"
#include "../graphics/Curses.hpp"
#include "../math/Point.hpp"
#include "../math/Rectangle.hpp"

namespace travail {
    class ILevelGenerator;
    
    class Level {
    public:
        Level(uint32_t depth, uint32_t width, uint32_t height,
              const std::vector<TileType> &ttypes, const ILevelGenerator &gen);
        Level(uint32_t depth, const Dimensions2u &dim,
              const std::vector<TileType> &ttypes, const ILevelGenerator &gen);
        ~Level();
        
        Tile & get(uint32_t x, uint32_t y);
        const Tile & get(uint32_t x, uint32_t y) const;
        
        void render(Window *win, Point2u dest, Point2u src = Point2u()) const;
        void render(Window *win, Point2u dest, Rectangle2u area) const;
    protected:
        std::allocator<Tile> m_allocator;
        const std::vector<TileType> &m_ttypes;
        Dimensions2u m_dim;
        Point2u m_center;
        uint32_t m_depth, m_tlen;
        Tile *m_tiles;
    };
    
}

#endif
