
#ifndef TRAVAIL_ATTRIBUTE_HPP
#define TRAVAIL_ATTRIBUTE_HPP

#include <stdint.h>
#include <limits>

namespace travail {
    class Attribute {
    public: //< Enumeration
        enum Id {
            HitPoints,
            FatiguePoints,
            Strength,
            Dexterity,
            Agility,
            Constitution,
            Intelligence,
            Wisdom,
            Charisma,
            
            HP  = HitPoints,
            FP  = FatiguePoints,
            STR = Strength,
            DEX = Dexterity,
            AGL = Agility,
            CON = Constitution,
            INT = Intelligence,
            WIS = Wisdom,
            CHA = Charisma,
            
            Length
        };
        
        enum Status {
            Zero,
            Bad,
            Poor,
            Damaged,
            Okay,
            Normal
        };
        
    public: //< Static API
        static const char * ShortName(Attribute::Id id);
        static const char * LongName(Attribute::Id id);
        
    public: // API
        Attribute();
        Attribute(int32_t value);
        Attribute(int32_t base, int32_t max, int32_t current);
        Attribute(const Attribute &source);
        ~Attribute();
        
        Attribute & operator=(const Attribute &rhs);
        
        void heal(int32_t amount = std::numeric_limits<int32_t>::max());
        void damage(int32_t amount);
        
        void incMax(int32_t amount = 1);
        void decMax(int32_t amount = 1);
        
        void incLevel(int32_t amount = 1);
        void decLevel(int32_t amount = 1);
        
        Attribute::Status status() const;
        
        int32_t base() const;
        int32_t maximum() const;
        int32_t current() const;
    protected: //< Data
        int32_t m_Base, m_Max, m_Current;
    };
}

#endif
