
#include "travail/graphics/PairMap.hpp"

#include "travail/graphics/Curses.hpp"

using namespace travail;

union PairHash {
    struct {
        int16_t fg;
        int16_t bg;
    } pair;
    int32_t hash;
};

PairMap::PairMap() :
    m_current(1)
{
    PairHash p;
    p.pair.fg = -1;
    p.pair.bg = -1;
    m_map[p.hash] = 0;
}
PairMap::~PairMap() { }

int32_t PairMap::get(int16_t fg, int16_t bg) {
    //TODO: Verify that fg and bg are ok.
    if(m_current >= COLOR_PAIRS || (fg < -1 || fg > COLORS - 1) ||
       (bg < -1 || bg > COLORS - 1))
    {
        return 0;
    }
       
    int32_t pair_id;
    PairHash p;
    p.pair.fg = fg;
    p.pair.bg = bg;
    auto iter = m_map.find(p.hash);
    if(iter == m_map.end()) {
        if(::init_pair(m_current, fg, bg) != OK) {
            return 0;
        }
        m_map[p.hash] = (pair_id = m_current);
        m_current += 1;
        return pair_id;
    }
    return (*iter).second;
}
