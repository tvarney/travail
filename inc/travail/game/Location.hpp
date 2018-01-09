
#ifndef TRAVAIL_GAME_LOCATION_HPP
#define TRAVAIL_GAME_LOCATION_HPP

#include <set>
#include "../graphics/Text.hpp"
#include "../util/Reference.hpp"

namespace travail {
    class GameObject;
    
    class Location {
    public: // static api
        static Location & Nowhere();
        
    public: // typedefs
        typedef std::set<Reference<Location> > EdgeList;
        typedef std::set<Reference<GameObject> > ObjectList;
    public: // API
        Location();
        Location(const std::string &name, const std::string &desc);
        ~Location() = default;
        
        const Text & name() const;
        const Text & description() const;
        
        void add(GameObject &object);
        void remove(GameObject &object);
        
        void add(Location &to);
        void remove(Location &to);
        
        EdgeList::iterator begin_edges();
        EdgeList::iterator end_edges();
        EdgeList::const_iterator cbegin_edges() const;
        EdgeList::const_iterator cend_edges() const;
        
        ObjectList::iterator begin_objects();
        ObjectList::iterator end_objects();
        ObjectList::const_iterator cbegin_objects() const;
        ObjectList::const_iterator cend_objects() const;
    protected:
        Text m_Name, m_Description;
        EdgeList m_Edges;
        ObjectList m_Objects;
    };
}

#endif
