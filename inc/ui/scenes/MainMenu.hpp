
#ifndef TRAVAIL_SCENES_MAIN_MENU_HPP
#define TRAVAIL_SCENES_MAIN_MENU_HPP

#include "../Option.hpp"
#include "../Scene.hpp"

#include "GameScene.hpp"
#include "NewGameScene.hpp"
#include "InfoScene.hpp"

namespace travail {
    class MainMenu : public Scene {
    public:
        MainMenu();
        virtual ~MainMenu();
        
        virtual void run();
        
        void moveCursor(std::size_t index);
    protected:
        GameScene m_Game;
        NewGameScene m_NewGame;
        InfoScene m_Info;
        
        //LoadGameScene m_LoadGame;
        //OptionsScene m_Options;
        Option m_Options;
        Label m_Title;
    };
}

#endif
