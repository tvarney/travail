#ifndef TRAVAIL_GAME_GAME_OBJECT_HPP
#define TRAVAIL_GAME_GAME_OBJECT_HPP

#include "Location.hpp"

namespace travail {
    class Text;
    
    class GameObject {
    public:
        GameObject(Reference<Location> ref = Location::Nowhere());
        virtual ~GameObject();
        
        virtual Location & location() const;
        virtual const Text & name() const = 0;
        virtual const Text & description() const = 0;
        
        virtual void setLocation(Location &location);
    protected:
        Reference<Location> m_Location; //< Disallow nullptr
    };
}

#endif
