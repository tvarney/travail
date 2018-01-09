
#ifndef TRAVAIL_NEW_GAME_SCENE_HPP
#define TRAVAIL_NEW_GAME_SCENE_HPP

#include "travail/ui/Scene.hpp"

#include "travail/ui/Column.hpp"
#include "travail/ui/Row.hpp"

namespace travail {
    class NewGameScene : public Scene {
    public:
        NewGameScene();
        virtual ~NewGameScene();
        
        virtual void run();
        virtual int handle(int ch);
    protected:
        bool m_Running;
        Column *m_Column;
        Row *m_Row;
    };
}

#endif
