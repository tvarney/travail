
#include "scenes/MainMenu.hpp"

#include <cctype>
#include <ncurses.h>
#include "SceneStack.hpp"

using namespace travail;

MainMenu::MainMenu() { }
MainMenu::~MainMenu() { }

void MainMenu::run() {
    int x = 0, y = 0, ch = KEY_RESIZE;
    do {
        if(std::isprint(ch)) {
            /* Ignore */
        }else {
            switch(ch) {
            case KEY_RESIZE:
                getmaxyx(stdscr, y, x);
                mvaddstr(0, (x / 2) - 4, "Main Menu");
                break;
            default:
                /* Ignore */
                break;
            }
        }
    } while((ch = getch()) != 27);
    
    m_Stack->pop();
}
