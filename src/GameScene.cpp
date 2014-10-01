
#include "ui/scenes/GameScene.hpp"

#include <cctype>
#include "ui/SceneStack.hpp"
#include "util/Curses.hpp"

using namespace travail;

GameScene::GameScene() { }
GameScene::~GameScene() { }
void GameScene::run() {
    mvwaddstr(stdscr, 0,0,"Game (Press ^Q to continue)");
    wrefresh(stdscr);
    
    int width, height;
    getmaxyx(stdscr, height, width);
    
    m_Buffer.clear();
    m_Buffer.setPos(height - 1);
    
    std::basic_string<chtype> div;
    div.resize(width, static_cast<chtype>(' ') | A_STANDOUT);
    
    mvwaddchstr(stdscr, height - 2, 0, div.data());
    
    int ch;
    while((ch = getch()) != 17) {
        switch(m_Buffer.handle(stdscr, ch)) {
        case 0:
            wrefresh(stdscr);
            break;
        case KEY_ENTER:
        case '\n':
        case '\r':
            m_Buffer.addToHistory(m_Buffer.data());
            m_Buffer.clear();
            m_Buffer.draw(stdscr);
            break;
        default:
            break;
        }
    }
    m_Stack->pop();
}
