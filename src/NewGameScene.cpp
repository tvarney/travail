
#include "ui/scenes/NewGameScene.hpp"

#include <ncurses.h>
#include "ui/SceneStack.hpp"

using namespace travail;

NewGameScene::NewGameScene() { }
NewGameScene::~NewGameScene() { }

void NewGameScene::run() {
    mvwaddstr(stdscr, 0,0,"New Game (Press any key to continue)");
    wrefresh(stdscr);
    getch();
    m_Stack->pop();
}
