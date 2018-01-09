
#include "travail/game/Race.hpp"

using namespace travail;

Race::Race(const std::string &name) :
    m_Name(name)
{ }
Race::~Race() { }

const std::string & Race::name() const {
    return m_Name;
}
