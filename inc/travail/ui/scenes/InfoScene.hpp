
#ifndef TRAVAIL_UI_SCENES_INFO_SCENE_HPP
#define TRAVAIL_UI_SCENES_INFO_SCENE_HPP

#include "travail/ui/Scene.hpp"

namespace travail {
    class InfoScene : public Scene {
    public:
        InfoScene();
        virtual ~InfoScene();
        
        virtual void draw() override;
        virtual int handle(int ch) override;
    };
}

#endif
