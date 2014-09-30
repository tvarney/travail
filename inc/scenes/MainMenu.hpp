
#ifndef TRAVAIL_SCENES_MAIN_MENU_HPP
#define TRAVAIL_SCENES_MAIN_MENU_HPP

#include "../Scene.hpp"
#include "../Label.hpp"

namespace travail {
    class MainMenu : public Scene {
    public:
        MainMenu();
        virtual ~MainMenu();
        
        virtual void run();
    protected:
        Label m_Title;
        Label m_NewGame;
        Label m_LoadGame;
        Label m_Options;
        Label m_Quit;
    };
}

#endif
