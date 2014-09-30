
#ifndef TRAVAIL_SCENE_STACK_HPP
#define TRAVAIL_SCENE_STACK_HPP

#include <cstddef>
#include <vector>

namespace travail {
    class Scene;
    
    class SceneStack {
    public:
        SceneStack() = default;
        ~SceneStack();
        
        void run();
        
        void push(Scene &scene);
        void pop();
        void swap(Scene &scene);
        
        void clear();
        
        std::size_t size() const;
    protected:
        std::vector<Scene *> m_Data;
    };
}

#endif
