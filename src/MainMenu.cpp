
#include "scenes/MainMenu.hpp"

#include <cctype>
#include <ncurses.h>
#include "SceneStack.hpp"

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
    m_Index = 0;
    
    do {
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
            m_Title.draw(stdscr);
            for(int i = 0; i < 4; ++i) {
                m_Labels[i].setPos(startx, 2+i);
                m_Labels[i].draw(stdscr);
            }
            m_Cursor.draw(stdscr, m_Labels[m_Index]);
            
            wrefresh(stdscr);
            break;
        case 'n':
        case 'N':
            if(m_Index != 0) {
                moveCursor(0);
            }
            break;
        case 'l':
        case 'L':
            if(m_Index != 1) {
                moveCursor(1);
            }
            break;
        case 'o':
        case 'O':
            if(m_Index != 2) {
                moveCursor(2);
            }
            break;
        case 'q':
        case 'Q':
            if(m_Index != 3) {
                moveCursor(3);
            }
            break;
        case KEY_UP:
        case 'u':
            if(m_Index > 0) {
                moveCursor(m_Index - 1);
            }
            break;
        case KEY_DOWN:
        case 'j':
            if(m_Index < 3) {
                moveCursor(m_Index + 1);
            }
            break;
        case KEY_ENTER:
            
            break;
        default:
            /* Ignore */
            break;
            }
    } while((ch = getch()) != 17);
    
    m_Stack->pop();
}

void MainMenu::moveCursor(std::size_t index) {
    m_Cursor.redraw(stdscr, m_Labels[m_Index], m_Labels[index]);
    m_Index = index;
    wrefresh(stdscr);
}
