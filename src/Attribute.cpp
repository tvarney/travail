
#include "game/Attribute.hpp"

using namespace travail;

// Static API
static const char * _g_Attr_LongName[] = {
    "Hit Points", "Fatigue Points", "Strength", "Dexterity", "Agility",
    "Constitution", "Intelligence", "Wisdom", "Charisma"
};
static const char * _g_Attr_ShortName[] = {
    "HP", "FP", "Str", "Dex", "Agl", "Con", "Int", "Wis", "Cha"
};

const char * Attribute::ShortName(Attribute::Id id) {
    if(id >= Attribute::Length || id < 0) {
        return "???";
    }
    return _g_Attr_ShortName[id];
}
const char * Attribute::LongName(Attribute::Id id) {
    if(id >= Attribute::Length || id < 0) {
        return "???";
    }
    return _g_Attr_LongName[id];
}

// API

Attribute::Attribute() :
    m_Base(10), m_Max(10), m_Current(10)
{ }
Attribute::Attribute(int32_t value) :
    m_Base(value), m_Max(value), m_Current(value)
{ }
Attribute::Attribute(int32_t base, int32_t max, int32_t current) :
    m_Base(base), m_Max(max), m_Current(current)
{ }
Attribute::Attribute(const Attribute &source) :
    m_Base(source.m_Base), m_Max(source.m_Max), m_Current(source.m_Current)
{ }
Attribute::~Attribute() { }

Attribute & Attribute::operator=(const Attribute &rhs) {
    m_Base    = rhs.m_Base;
    m_Max     = rhs.m_Max;
    m_Current = rhs.m_Current;
    return *this;
}

void Attribute::heal(int32_t amount) {
    if(amount > m_Max - m_Current) {
        m_Current = m_Max;
    }else {
        m_Current += amount;
    }
}

void Attribute::damage(int32_t amount) {
    m_Current -= amount;
}

void Attribute::incMax(int32_t amount) {
    m_Max += amount;
}
void Attribute::decMax(int32_t amount) {
    m_Max -= amount;
    if(m_Current > m_Max) {
        m_Current = m_Max;
    }
}

void Attribute::incLevel(int32_t amount) {
    m_Base += amount;
    m_Max += amount;
}
void Attribute::decLevel(int32_t amount) {
    m_Base -= amount;
    m_Max -= amount;
}

Attribute::Status Attribute::status() const {
    if(m_Current <= 0) return Attribute::Zero;
    if(m_Current <= (m_Max >> 3)) return Attribute::Bad;
    if(m_Current <= (m_Max >> 2)) return Attribute::Poor;
    if(m_Current <= (m_Max >> 1)) return Attribute::Damaged;
    if(m_Current <= ((m_Max >> 1) + (m_Max >> 2))) return Attribute::Okay;
    return Attribute::Normal;
}
