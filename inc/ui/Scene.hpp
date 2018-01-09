
#ifndef TRAVAIL_SCENE_HPP
#define TRAVAIL_SCENE_HPP

namespace travail {
    class SceneStack;
    
    class Scene {
    public:
        Scene();
        virtual ~Scene();
        
        virtual void start();
        virtual void stop();
        
        virtual void pause();
        virtual void resume();
        
        virtual void run() = 0;
        virtual void handle(int ch) = 0;
        
        void set_stack(SceneStack & stack);
    protected:
        SceneStack *m_Stack;
    };
}

#endif
