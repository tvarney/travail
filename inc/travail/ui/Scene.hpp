
#ifndef TRAVAIL_SCENE_HPP
#define TRAVAIL_SCENE_HPP

#include "travail/ui/Container.hpp"

namespace travail {
    class SceneStack;
    
    class Scene : public Container {
    public:
        Scene();
        virtual ~Scene();
        
        virtual void start();
        virtual void stop();
        
        virtual void pause();
        virtual void resume();
        
        virtual int handle(int ch) = 0;
        
        void set_stack(SceneStack & stack);
    protected:
        SceneStack *m_Stack;
    };
}

#endif
