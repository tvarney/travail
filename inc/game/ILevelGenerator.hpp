
#ifndef TRAVAIL_GAME_I_LEVEL_GENERATOR_HPP
#define TRAVAIL_GAME_I_LEVEL_GENERATOR_HPP

#include <vector>
#include "Tile.hpp"
#include "../math/Dimensions.hpp"

namespace travail {
    class ILevelGenerator {
    public:
        virtual ~ILevelGenerator();
        
        /**
         * \brief Generate a new level given the depth, dimensions and empty
         * memory region.
         * 
         * The tile array given to this function is expected to be allocated
         * with an allocator; that is, non-constructed. Any class implementing
         * this interface should construct the Tiles, not copy them.
         * 
         * The tile array must be (dim.width * dim.height) in size. Classes
         * implementing this interface are free to assume this will hold true
         * at all times. Failure to give the generator a large enough space
         * will result in segfaults. Don't do that.
         * 
         * \arg depth The depth of the level being generated
         * \arg dim The dimensions of the level
         * \arg types The vector of tile types to use
         * \arg tiles The tile array, allocated by an allocator.
         */
        virtual void generate(uint32_t depth, const Dimensions2u &dim,
                              const std::vector<TileType> &types,
                              Tile *tiles) const = 0;
    protected:
        ILevelGenerator();
    };
}

#endif
