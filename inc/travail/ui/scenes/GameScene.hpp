
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
        virtual void handle(int ch);
    protected:
        bool m_Running;
        CommandBuffer m_Buffer;
    };
}

#endif
