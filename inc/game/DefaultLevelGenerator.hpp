
#ifndef TRAVAIL_GAME_DEFAULT_LEVEL_GENERATOR_HPP
#define TRAVAIL_GAME_DEFAULT_LEVEL_GENERATOR_HPP

#include "ILevelGenerator.hpp"

namespace travail {
    class DefaultLevelGenerator : public ILevelGenerator {
    public:
        DefaultLevelGenerator(uint16_t wall, uint16_t floor, uint16_t upstair,
                              uint16_t downstair);
        virtual ~DefaultLevelGenerator();
        
        virtual void generate(uint32_t depth, const Dimensions2u &dim,
                              const std::vector<TileType> &types,
                              Tile *tiles) const;
    private:
        uint16_t m_wallid, m_floorid, m_upstairid, m_downstairid;
    };
}

#endif
