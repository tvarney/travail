
#ifndef TRAVAIL_NEW_GAME_SCENE_HPP
#define TRAVAIL_NEW_GAME_SCENE_HPP

#include "../Scene.hpp"
#include "GameScene.hpp"

namespace travail {
    class NewGameScene : public Scene {
    public:
        NewGameScene();
        virtual ~NewGameScene();
        
        virtual void run();
    protected:
        
    };
}

#endif
