
#include "ui/Scene.hpp"

using namespace travail;

Scene::Scene() :
    m_Stack(nullptr)
{ }
Scene::~Scene() { }

void Scene::start() { }
void Scene::stop() { }
void Scene::pause() { }
void Scene::resume() { }

void Scene::set_stack(SceneStack & stack) {
    if(m_Stack != nullptr) {
        throw "Scene::set_stack(): Method called multiple times";
    }
    m_Stack = &stack;
}
