
#ifndef TRAVAIL_ATTRIBUTE_HPP
#define TRAVAIL_ATTRIBUTE_HPP

#include <stdint.h>

namespace travail {
    struct Attribute {
        enum Id {
            STR = 0,
            Strength = 0,
            DEX = 1,
            Dexterity = 1,
            AGL = 2,
            Agility = 2,
            CON = 3,
            Constitution = 3,
            INT = 4,
            Intelligence = 4,
            WIS = 5,
            Wisdom = 5,
            CHA = 6,
            Charisma = 6,
            
            AttributeNumber
        };
        
        Attribute(uint32_t value);
        Attribute(uint32_t current, uint32_t max);
        ~Attribute();
        
        static const char * Name(Attribute::Id id);
        static const char * LongName(Attribute::Id id);
        
        uint32_t current;
        uint32_t max;
    };
}

#endif
