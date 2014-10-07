
#include "game/Location.hpp"

using namespace travail;

Location & Location::Nowhere() {
    static Location _nowhere;
    return _nowhere;
}

Location::Location() :
    m_Name("Nowhere"),
    m_Description("An empty void outside of space and time")
{ }
Location::Location(const std::string &name, const std::string &desc) :
    m_Name(name), m_Description(desc)
{ }

void Location::add(GameObject &object) {
    m_Objects.insert(Reference<GameObject>(object));
}
void Location::remove(GameObject &object) {
    m_Objects.erase(Reference<GameObject>(object));
}

void Location::add(Location &to) {
    m_Edges.insert(Reference<Location>(to));
}
void Location::remove(Location &to) {
    m_Edges.erase(Reference<Location>(to));
}

Location::EdgeList::iterator Location::begin_edges() {
    return m_Edges.begin();
}
Location::EdgeList::iterator Location::end_edges() {
    return m_Edges.end();
}

Location::EdgeList::const_iterator Location::cbegin_edges() const {
    return m_Edges.cbegin();
}
Location::EdgeList::const_iterator Location::cend_edges() const {
    return m_Edges.cend();
}

Location::ObjectList::iterator Location::begin_objects() {
    return m_Objects.begin();
}
Location::ObjectList::iterator Location::end_objects() {
    return m_Objects.end();
}
Location::ObjectList::const_iterator Location::cbegin_objects() const {
    return m_Objects.cbegin();
}
Location::ObjectList::const_iterator Location::cend_objects() const {
    return m_Objects.cend();
}
