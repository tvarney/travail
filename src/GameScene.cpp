
#include "ui/scenes/GameScene.hpp"

#include <cctype>
#include <ncurses.h>
#include "ui/SceneStack.hpp"

using namespace travail;

GameScene::GameScene() { }
GameScene::~GameScene() { }
void GameScene::run() {
    mvwaddstr(stdscr, 0,0,"Game (Press any key to continue)");
    wrefresh(stdscr);
    getch();
    m_Stack->pop();
}
