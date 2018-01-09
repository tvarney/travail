
#include "ui/scenes/MainMenu.hpp"

#include <cctype>
#include "graphics/Curses.hpp"
#include "ui/Option.hpp"
#include "ui/Orientation.hpp"
#include "ui/SceneStack.hpp"
#include "util/Keys.hpp"

using namespace travail;

MainMenu::MainMenu() :
    m_Options(Orientation::Vertical, 0, 2),
    m_Title(0, 0, "Travail Text RPG", COLOR_PAIR(1) | A_BOLD)
{
    m_Options.add("New Game");
    m_Options.add("Load Game");
    m_Options.add("Options");
    m_Options.add("Terminfo");
    m_Options.add("Quit");
}
MainMenu::~MainMenu() { }

void MainMenu::run() {
    int ch = 0;//, startx;
    m_Running = true;
    
    m_Title.center_h(getmaxx(stdscr));
    m_Title.draw();
    m_Options.center_h(getmaxx(stdscr));
    m_Options.setSelectedAttrib(A_BOLD | A_UNDERLINE);
    m_Options.setUnselectedAttrib(A_DIM);
    m_Options.draw();
    
#ifndef NDEBUG
    mvprintw(getmaxy(stdscr)-2,0, "%s [%d]", keyname(ch),ch);
    clrtoeol();
#endif
    
    while(m_Running) {
        ch = travail::wgetch(stdscr);
#ifndef NDEBUG
        mvprintw(getmaxy(stdscr)-2,0, "%s [%d]", keyname(ch),ch);
        clrtoeol();
#endif
        handle(ch);
    };
}

void MainMenu::handle(int ch) {
    if(ch == 17) {
        m_Running = false;
        m_Stack->clear();
        return;
    }
    
    switch(m_Options.handle(ch)) {
    case KEY_RESIZE:
        wclear(stdscr);
        m_Title.center_h(getmaxx(stdscr));
        m_Options.center_h(getmaxx(stdscr));
        m_Title.draw();
        m_Options.draw();
        //m_Cursor.point(m_Labels[m_Index]);
            
        wrefresh(stdscr);
        break;
    case 'n':
    case 'N':
        if(m_Options.getChosenInt() == 0) {
            m_Stack->push("NewGame");
            return;
        }else {
            m_Options.setChoice(0);
            wrefresh(stdscr);
        }
        break;
    case 'l':
    case 'L':
        if(m_Options.getChosenInt() == 1) {
            m_Stack->push("Game");
            return;
        }else {
            m_Options.setChoice(1);
            wrefresh(stdscr);
        }
        break;
    case 'o':
    case 'O':
        if(m_Options.getChosenInt() == 2) {
            m_Stack->push("Game");
            return;
        }else {
            m_Options.setChoice(2);
            wrefresh(stdscr);
        }
        break;
    case 'i':
    case 'I':
        if(m_Options.setChoice(3)) {
            wrefresh(stdscr);
        }else {
            m_Stack->push("Info");
            return;
        }
        break;
    case 'q':
    case 'Q':
        if(!(m_Options.setChoice(4))) {
            m_Running = false;
        }else {
            wrefresh(stdscr);
        }
        break;
    case KEY_ENTER:
    case '\n':
    case '\r':
        switch(m_Options.getChosenInt()) {
        case 0:
            m_Stack->push("NewGame");
            break;
        case 1:
        case 2:
            m_Stack->push("Game");
            break;
        case 3:
            m_Stack->push("Info");
            break;
        case 4:
            break;
        }
        m_Running = false;
        break;
    case 0:
        wrefresh(stdscr);
    default:
#ifndef NDEBUG
        mvprintw(getmaxy(stdscr)-1,0,"Choice: %d",
                 m_Options.getChosenInt());
        wrefresh(stdscr);
#endif
        /* Ignore */
        break;
    }
}
