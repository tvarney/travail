
#include "game/Tile.hpp"

using namespace travail;

Tile::Tile(uint16_t id, uint16_t flags) :
    tileid(id), flags(flags)
{ }

void Tile::write(Window *win, const std::vector<TileType> &ttypes) const {
    waddch(win, ttypes[tileid].glyph);
}
