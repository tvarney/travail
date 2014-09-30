
#include "game/Attribute.hpp"

using namespace travail;

Attribute::Attribute(uint32_t value) :
    current(value), max(value)
{ }
Attribute::Attribute(uint32_t current, uint32_t max) :
    current(current), max(max)
{ }
Attribute::~Attribute() { }

const char * Attribute::Name(Attribute::Id id) {
    switch(id) {
    case STR:
        return "STR";
    case DEX:
        return "DEX";
    case AGL:
        return "AGL";
    case CON:
        return "CON";
    case INT:
        return "INT";
    case WIS:
        return "WIS";
    case CHA:
        return "CHA";
    default:
        return "???";
    }
}
const char * Attribute::LongName(Attribute::Id id) {
    switch(id) {
    case STR:
        return "Strength";
    case DEX:
        return "Dexterity";
    case AGL:
        return "Agility";
    case CON:
        return "Constitution";
    case INT:
        return "Intelligence";
    case WIS:
        return "Wisdom";
    case CHA:
        return "Charisma";
    default:
        return "???";
    }
}
