
#include "scenes/MainMenu.hpp"

#include <cctype>
#include <ncurses.h>
#include "SceneStack.hpp"

using namespace travail;

MainMenu::MainMenu() :
    m_Title(0, 0, "Travail Text RPG", COLOR_PAIR(1) | A_BOLD),
    m_NewGame(0, 2, "New Game"),
    m_LoadGame(0, 3, "Load Game"),
    m_Options(0, 4, "Options"),
    m_Quit(0, 5, "Quit")
{ }
MainMenu::~MainMenu() { }

void MainMenu::run() {
    int ch = KEY_RESIZE, startx;
    do {
        if(std::isprint(ch)) {
            /* Ignore */
        }else {
            switch(ch) {
            case KEY_RESIZE:
                startx = (getmaxx(stdscr)-m_LoadGame.getDim().width) >> 1;
                
                m_Title.center_h(getmaxx(stdscr));
                m_NewGame.setPos(startx, 2);
                m_LoadGame.setPos(startx, 3);
                m_Options.setPos(startx, 4);
                m_Quit.setPos(startx, 5);
                
                m_Title.draw(stdscr);
                m_NewGame.draw(stdscr);
                m_LoadGame.draw(stdscr);
                m_Options.draw(stdscr);
                m_Quit.draw(stdscr);
                
                wrefresh(stdscr);
                break;
            default:
                /* Ignore */
                break;
            }
        }
    } while((ch = getch()) != 27);
    
    m_Stack->pop();
}
