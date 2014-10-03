
#include "ui/scenes/MainMenu.hpp"

#include <cctype>
#include "ui/SceneStack.hpp"
#include "util/Curses.hpp"
#include "util/Keys.hpp"

using namespace travail;

MainMenu::MainMenu() :
    m_Cursor("*", A_BOLD),
    m_Title(0, 0, "Travail Text RPG", COLOR_PAIR(1) | A_BOLD),
    m_Labels{{0,2,"New Game"},{0,3,"Load Game"},{0,4,"Options"},{0,5,"Quit"}}
{ }
MainMenu::~MainMenu() { }

void MainMenu::run() {
    int ch = KEY_RESIZE, startx;
    std::size_t maxw, len;
    bool running = true;
    m_Index = 0;
    
    do {
#ifndef NDEBUG
        mvprintw(getmaxy(stdscr)-2,0, "%s [%d]", keyname(ch),ch);
        clrtoeol();
#endif
        switch(ch) {
        case KEY_RESIZE:
            maxw = 0;
            for(int i = 0; i < 4; ++i) {
                len = m_Labels[i].getText().size();
                if(len > maxw) {
                    maxw = len;
                }
            }
            startx = (getmaxx(stdscr) - maxw) >> 1;
                
            m_Title.center_h(getmaxx(stdscr));
            m_Title.draw();
            for(int i = 0; i < 4; ++i) {
                m_Labels[i].setPos(startx, 2+i);
                m_Labels[i].draw();
            }
            m_Cursor.point(m_Labels[m_Index]);
            
            wrefresh(stdscr);
            break;
        case 'n':
        case 'N':
            if(m_Index != 0) {
                moveCursor(0);
            }else {
                m_Stack->push(m_Game);
                m_Stack->push(m_NewGame);
                return;
            }
            break;
        case 'l':
        case 'L':
            if(m_Index != 1) {
                moveCursor(1);
            }else {
                m_Stack->push(m_Game);
                return;
            }
            break;
        case 'o':
        case 'O':
            if(m_Index != 2) {
                moveCursor(2);
            }else {
                m_Stack->push(m_Game); //TODO: Replace with m_Options
                return;
            }
            break;
        case 'q':
        case 'Q':
            if(m_Index != 3) {
                moveCursor(3);
            }else {
                running = false;
            }
            break;
        case KEY_UP:
        case travail::cntrl('b'):
        case travail::cntrl('p'):
            if(m_Index > 0) {
                moveCursor(m_Index - 1);
            }
            break;
        case KEY_DOWN:
        case travail::cntrl('f'):
        case travail::cntrl('n'):
            if(m_Index < 3) {
                moveCursor(m_Index + 1);
            }
            break;
        case KEY_ENTER:
        case '\n':
        case '\r':
            switch(m_Index) {
            case 0:
                m_Stack->push(m_Game);
                m_Stack->push(m_NewGame);
                return; //< Return so the scene stack can swap to the new scene
            case 1:
                break;
            case 2:
                break;
            case 3:
                running = false;
                break;
            }
            break;
        default:
#ifndef NDEBUG
            wrefresh(stdscr);
#endif
            /* Ignore */
            break;
        }
    } while(running && (ch = travail::wgetch(stdscr)) != 17);
    
    m_Stack->pop();
}

void MainMenu::moveCursor(std::size_t index) {
#ifndef NDEBUG
    mvprintw(getmaxy(stdscr)-1,0, "m_Index: %llu",
             (long long unsigned)index);
#endif
    m_Index = index;
    m_Cursor.move(m_Labels[m_Index]);
    wrefresh(stdscr);
}
