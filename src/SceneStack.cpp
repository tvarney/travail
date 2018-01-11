
#include "travail/ui/SceneStack.hpp"

#include <stdexcept>

#include "travail/ui/Scene.hpp"
#include "travail/graphics/Curses.hpp"

using namespace travail;

SceneStack::SceneStack() :
    m_Window(nullptr)
{ }
SceneStack::~SceneStack() {
    (*this).clear();
}

void SceneStack::setWindow(WINDOW * win) {
    m_Window = win;
    for(auto it = m_Scenes.begin(); it != m_Scenes.end(); ++it) {
        it->second->setWindow(win);
    }
}

void SceneStack::push(const std::string & id) {
    auto iter = m_Scenes.find(id);
    if(iter != m_Scenes.end()) {
        if(m_Data.size() > 0) {
            (*(m_Data.back())).pause();
        }
        ::wclear(stdscr);
        (*(iter->second)).start();
        (*(iter->second)).draw();
        m_Data.push_back(iter->second);
    }
}

void SceneStack::pop() {
    if(m_Data.size() > 0) {
        Scene &back = (*(m_Data.back()));
        back.stop();
        m_Data.pop_back();
        
        if(m_Data.size() > 0) {
            ::wclear(stdscr);
            (*(m_Data.back())).resume();
            (*(m_Data.back())).draw();
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
        ::wclear(stdscr);
        (*(iter->second)).start();
        (*(iter->second)).draw();
    }
}

void SceneStack::clear() {
    for(std::size_t len = m_Data.size(); len > 0; --len) {
        Scene &scene = *(m_Data.back());
        scene.stop();
        m_Data.pop_back();
    }
}

SceneStack::SceneRef & SceneStack::peek() {
    if(m_Data.size() > 0) {
        return m_Data.back();
    }
    // TODO: Use a different (more specific) exception here
    throw std::runtime_error("SceneStack::peek(): Called on empty stack");
}

const SceneStack::SceneRef & SceneStack::peek() const {
    if(m_Data.size() > 0) {
        return m_Data.back();
    }
    throw std::runtime_error("SceneStack::peek(): Called on empty stack");
}

std::size_t SceneStack::size() const {
    return m_Data.size();
}

bool SceneStack::add_impl(const std::string & id, SceneRef & scene) {
    auto p = m_Scenes.insert({id, scene});
    if(p.second) {
        scene->set_stack(*this);
        scene->setWindow(m_Window);
    }
    return p.second;
}
