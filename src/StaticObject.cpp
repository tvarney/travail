
#include "game/StaticObject.hpp"

using namespace travail;

StaticObject::StaticObject() :
    m_Name("Nothing"), m_Description("Absolutely nothing")
{ }
StaticObject::StaticObject(const Text &name, const Text &desc) :
    m_Name(name), m_Description(desc)
{ }
StaticObject::~StaticObject() { }

const Text & StaticObject::name() const {
    return m_Name;
}
const Text & StaticObject::description() const {
    return m_Description;
}
