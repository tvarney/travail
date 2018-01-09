
#ifndef TRAVAIL_UI_SCENES_INFO_SCENE_HPP
#define TRAVAIL_UI_SCENES_INFO_SCENE_HPP

#include "travail/ui/Scene.hpp"

namespace travail {
    class InfoScene : public Scene {
    public:
        InfoScene();
        virtual ~InfoScene();
        
        virtual void run();
        virtual void handle(int ch);
    private:
        bool m_Running;
    };
}

#endif
