
#ifndef TRAVAIL_SCENES_MAIN_MENU_HPP
#define TRAVAIL_SCENES_MAIN_MENU_HPP

#include "../Option.hpp"
#include "../Scene.hpp"

namespace travail {
    class MainMenu : public Scene {
    public:
        MainMenu();
        virtual ~MainMenu();
        
        virtual void start();
        virtual int handle(int ch);
    protected:
        std::shared_ptr<Option> m_Options;
    };
}

#endif
