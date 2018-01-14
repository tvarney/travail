
#include "travail/ui/Scene.hpp"

using namespace travail;

const std::string Scene::ClassName("Scene");

Scene::Scene(const std::string & name) :
    Container(name), m_Stack(nullptr)
{ }
Scene::~Scene() { }

void Scene::start() { }
void Scene::stop() { }
void Scene::pause() { }
void Scene::resume() { }

const std::string & Scene::classname() const {
    return Scene::ClassName;
}

void Scene::set_stack(SceneStack & stack) {
    if(m_Stack != nullptr) {
        throw "Scene::set_stack(): Method called multiple times";
    }
    m_Stack = &stack;
}
