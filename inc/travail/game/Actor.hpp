
#pragma once
#ifndef TRAVAIL_GAME_ACTOR_HPP
#define TRAVAIL_GAME_ACTOR_HPP

#include <string>

#include "travail/game/Attribute.hpp"

namespace travail {
    class Actor {
    public:
        virtual ~Actor();
        
        virtual const std::string & name() const = 0;
        
        virtual Attribute & getAttribute(Attribute::Id id);
        virtual const Attribute & getAttribute(Attribute::Id id) const;
    protected:
        Actor();
        
        Attribute m_Attributes[7];
    };
}

#endif
