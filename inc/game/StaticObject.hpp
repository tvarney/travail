
#ifndef TRAVAIL_GAME_STATIC_OBJECT_HPP
#define TRAVAIL_GAME_STATIC_OBJECT_HPP

#include "GameObject.hpp"

namespace travail {
    class StaticObject : public GameObject {
    public:
        StaticObject();
        StaticObject(const Text &name, const Text &desc);
        virtual ~StaticObject();
        
        virtual const Text & name() const;
        virtual const Text & description() const;
    protected:
        Text m_Name, m_Description;
    };
}

#endif
