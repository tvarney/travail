
#pragma once
#ifndef TRAVAIL_GAME_PLAYER_HPP
#define TRAVAIL_GAME_PLAYER_HPP

#include "travail/game/Actor.hpp"

namespace travail {
    class Player {
    public:
        Player();
        ~Player();
        
        const std::string & name() const;
    private:
        std::string m_Name;
    };
}

#endif
