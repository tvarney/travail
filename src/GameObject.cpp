
#include "game/GameObject.hpp"

using namespace travail;

GameObject::GameObject(Reference<Location> ref) :
    m_Location(ref)
{
    m_Location.get().add(*this);
}
GameObject::~GameObject() {
    m_Location.get().remove(*this);
}

Location & GameObject::location() const {
    return m_Location.get();
}

void GameObject::setLocation(Location &location) {
    m_Location.set(location);
}
