
#ifndef TRAVAIL_SCENE_STACK_HPP
#define TRAVAIL_SCENE_STACK_HPP

#include <cstddef>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "travail/graphics/Curses.hpp"

namespace travail {
    class Scene;
    
    class SceneStack {
    public:
        typedef std::shared_ptr<Scene> SceneRef;
        
    public:
        SceneStack();
        ~SceneStack();
        
        void run();

        template <typename T>
        bool add(const std::string & id, std::shared_ptr<T> scene) {
            SceneRef r = scene;
            return add_impl(id, r);
        }
        bool remove(const std::string & id);
        
        void setWindow(WINDOW * win);
        
        void push(const std::string & id);
        void pop();
        void swap(const std::string & id);
        
        void clear();
        
        std::size_t size() const;
    protected:
        bool add_impl(const std::string & id, SceneRef & scene);
        
        WINDOW * m_Window;
        std::vector<std::shared_ptr<Scene>> m_Data;
        std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
    };
}

#endif
