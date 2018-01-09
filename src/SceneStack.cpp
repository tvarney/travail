
#include "ui/SceneStack.hpp"

#include "ui/Scene.hpp"
#include "graphics/Curses.hpp"

using namespace travail;

SceneStack::~SceneStack() {
    (*this).clear();
}

void SceneStack::run() {
    while(m_Data.size() > 0) {
        ::clear(); //< Name conflict, make sure the empty namespace is used
        (*(m_Data.back())).run();
    }
}

void SceneStack::push(const std::string & id) {
    auto iter = m_Scenes.find(id);
    if(iter != m_Scenes.end()) {
        if(m_Data.size() > 0) {
            (*(m_Data.back())).pause();
        }
        (*(iter->second)).start();
        m_Data.push_back(iter->second);
    }
}

void SceneStack::pop() {
    if(m_Data.size() > 0) {
        Scene &back = (*(m_Data.back()));
        back.stop();
        m_Data.pop_back();
        
        if(m_Data.size() > 0) {
            (*(m_Data.back())).resume();
        }
    }
}

void SceneStack::swap(const std::string & id) {
    auto iter = m_Scenes.find(id);
    if(iter != m_Scenes.end()) {
        if(m_Data.size() > 0) {
            Scene &back = *(m_Data.back());
            back.stop();
            m_Data.pop_back();
        }
        m_Data.push_back(iter->second);
        (*(iter->second)).start();
    }
}

void SceneStack::clear() {
    for(std::size_t len = m_Data.size(); len > 0; --len) {
        Scene &scene = *(m_Data.back());
        scene.stop();
        m_Data.pop_back();
    }
}

std::size_t SceneStack::size() const {
    return m_Data.size();
}

bool SceneStack::add_impl(const std::string & id, SceneRef & scene) {
    auto p = m_Scenes.insert({id, scene});
    if(p.second) {
        scene->set_stack(*this);
    }
    return p.second;
}
