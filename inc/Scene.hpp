
#ifndef TRAVAIL_SCENE_HPP
#define TRAVAIL_SCENE_HPP

namespace travail {
    class SceneStack;
    
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene();
        
        virtual void start();
        virtual void stop();
        
        virtual void pause();
        virtual void resume();
        
        virtual void run() = 0;
    protected:
        friend class SceneStack;
        SceneStack *m_Stack;
    };
}

#endif
