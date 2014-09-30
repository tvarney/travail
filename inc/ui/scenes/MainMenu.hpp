
#ifndef TRAVAIL_SCENES_MAIN_MENU_HPP
#define TRAVAIL_SCENES_MAIN_MENU_HPP

#include "../Cursor.hpp"
#include "../Label.hpp"
#include "../Scene.hpp"

namespace travail {
    class MainMenu : public Scene {
    public:
        MainMenu();
        virtual ~MainMenu();
        
        virtual void run();
        
        void moveCursor(std::size_t index);
    protected:
        std::size_t m_Index;
        Cursor m_Cursor;
        Label m_Title;
        Label m_Labels[4];
    };
}

#endif
