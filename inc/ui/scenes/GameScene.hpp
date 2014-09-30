
#ifndef TRAVAIL_SCENES_GAME_SCENE_HPP
#define TRAVAIL_SCENES_GAME_SCENE_HPP

#include "../CommandBuffer.hpp"
#include "../Scene.hpp"

namespace travail {
    class GameScene : public Scene {
    public:
        GameScene();
        virtual ~GameScene();
        
        virtual void run();
    protected:
        CommandBuffer m_Buffer;
    };
}

#endif
