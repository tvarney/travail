
#ifndef TRAVAIL_SCENES_GAME_SCENE_HPP
#define TRAVAIL_SCENES_GAME_SCENE_HPP

#include "../Scene.hpp"

namespace travail {
    class GameScene : public Scene {
    public:
        GameScene();
        virtual ~GameScene();
        
        virtual void run();
    };
}

#endif
