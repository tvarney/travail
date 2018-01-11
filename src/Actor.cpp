
#include "travail/game/Actor.hpp"

using namespace travail;

Actor::Actor() { }
Actor::~Actor() { }

Attribute & Actor::getAttribute(Attribute::Id id) {
    return m_Attributes[id];
}

const Attribute & Actor::getAttribute(Attribute::Id id) const {
    return m_Attributes[id];
}
