
#include "travail/ui/scenes/MainMenu.hpp"

#include <cctype>
#include "travail/graphics/Curses.hpp"
#include "travail/ui/Option.hpp"
#include "travail/ui/Orientation.hpp"
#include "travail/ui/SceneStack.hpp"
#include "travail/util/Keys.hpp"

#ifndef NDEBUG
# include <iostream>
#endif

using namespace travail;

MainMenu::MainMenu() :
    Scene("MainMenu"),
    m_Options(std::make_shared<Option>(Orientation::Vertical, 0, 2))
{
    add(new Label(Point2i(0, 0), "Travail Text RPG", COLOR_PAIR(1) | A_BOLD));
    m_Options->add("New Game");
    m_Options->add("Load Game");
    m_Options->add("Options");
    m_Options->add("Terminfo");
    m_Options->add("Quit");
    m_Options->setSelectedAttrib(A_BOLD | A_UNDERLINE);
    m_Options->setUnselectedAttrib(A_BOLD);
    add(m_Options);
}

MainMenu::~MainMenu() { }

void MainMenu::start() {
#ifndef NDEBUG
    std::cout << "MainMenu::start(): WINDOW *m_Window = " << m_Window <<
        std::endl;
#endif
    m_Children[0]->center_h(getmaxx(m_Window));
    m_Children[1]->center_h(getmaxx(m_Window));
#ifndef NDEBUG
    mvprintw(getmaxy(stdscr)-2,0, "%s [%d]", keyname(0),0);
    clrtoeol();
#endif
}

int MainMenu::handle(int ch) {
    if(ch == 17) {
        m_Stack->clear();
        return 0;
    }
    
#ifndef NDEBUG
        mvprintw(getmaxy(stdscr)-2,0, "%s [%d]", keyname(ch),ch);
        clrtoeol();
#endif
    
    switch(m_Options->handle(ch)) {
    case KEY_RESIZE:
        wclear(m_Window);
        m_Children[0]->center_h(getmaxx(m_Window));
        m_Children[1]->center_h(getmaxx(m_Window));
        draw();
        //m_Cursor.point(m_Labels[m_Index]);
        
        wrefresh(stdscr);
        return 0;
    case 'n':
    case 'N':
        if(m_Options->getChosenInt() == 0) {
            m_Stack->push("NewGame");
        }else {
            m_Options->setChoice(0);
            wrefresh(stdscr);
        }
        return 0;
    case 'l':
    case 'L':
        if(m_Options->getChosenInt() == 1) {
            m_Stack->push("Game");
        }else {
            m_Options->setChoice(1);
            wrefresh(stdscr);
        }
        return 0;
    case 'o':
    case 'O':
        if(m_Options->getChosenInt() == 2) {
            m_Stack->push("Game");
        }else {
            m_Options->setChoice(2);
            wrefresh(stdscr);
        }
        return 0;
    case 'i':
    case 'I':
        if(m_Options->getChosenInt() == 3) {
            m_Stack->push("Info");
        }else {
            m_Options->setChoice(3);
            wrefresh(m_Window);
        }
        return 0;
    case 'q':
    case 'Q':
        if(m_Options->getChosenInt() == 4) {
            m_Stack->pop();
        }else {
            m_Options->setChoice(4);
            wrefresh(m_Window);
        }
        return 0;
    case KEY_ENTER:
    case '\n':
    case '\r':
        switch(m_Options->getChosenInt()) {
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
            m_Stack->pop();
            break;
        }
        return 0;
    case 0:
        wrefresh(m_Window);
    default:
#ifndef NDEBUG
        mvprintw(getmaxy(m_Window)-1,0,"Choice: %d",
                 m_Options->getChosenInt());
        wrefresh(m_Window);
#endif
        /* Ignore */
        return ch;
    }
}
