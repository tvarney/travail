
#include "ui/SceneStack.hpp"

#include "ui/Scene.hpp"
#include "graphics/Curses.hpp"

using namespace travail;

SceneStack::~SceneStack() {
    (*this).clear();
}

void SceneStack::run() {
    while(m_Data.size() > 0) {
        ::clear(); //< Name conflict, make sure the emtpy namespace is used
        (*(m_Data.back())).run();
    }
}

void SceneStack::push(Scene &scene) {
    if(m_Data.size() > 0) {
        (*(m_Data.back())).pause();
    }
    scene.m_Stack = this;
    scene.start();
    m_Data.push_back(&scene);
}

void SceneStack::pop() {
    if(m_Data.size() > 0) {
        Scene &back = (*(m_Data.back()));
        back.stop();
        back.m_Stack = nullptr;
        m_Data.pop_back();
        
        if(m_Data.size() > 0) {
            (*(m_Data.back())).resume();
        }
    }
}

void SceneStack::swap(Scene &scene) {
    if(m_Data.size() > 0) {
        Scene &back = *(m_Data.back());
        back.stop();
        back.m_Stack = nullptr;
        m_Data.pop_back();
        
        scene.m_Stack = this;
        scene.start();
    }else {
        push(scene);
    }
}

void SceneStack::clear() {
    for(std::size_t len = m_Data.size(); len > 0; --len) {
        Scene &scene = *(m_Data.back());
        scene.stop();
        scene.m_Stack = nullptr;
        m_Data.pop_back();
    }
}

std::size_t SceneStack::size() const {
    return m_Data.size();
}
