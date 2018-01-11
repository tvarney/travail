
#include "travail/game/Player.hpp"

using namespace travail;

Player::Player() :
    m_Name("Rand Al'Thor")
{ }

Player::~Player() { }

const std::string & Player::name() const {
    return m_Name;
}
