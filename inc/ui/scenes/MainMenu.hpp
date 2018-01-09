
#ifndef TRAVAIL_SCENES_MAIN_MENU_HPP
#define TRAVAIL_SCENES_MAIN_MENU_HPP

#include "../Option.hpp"
#include "../Scene.hpp"

namespace travail {
    class MainMenu : public Scene {
    public:
        MainMenu();
        virtual ~MainMenu();
        
        virtual void run();
        virtual void handle(int ch);
        
        void moveCursor(std::size_t index);
    protected:
        bool m_Running;
        Option m_Options;
        Label m_Title;
    };
}

#endif
