
#include "travail/ui/scenes/GameScene.hpp"

#include <cctype>
#include "travail/graphics/Curses.hpp"
#include "travail/ui/SceneStack.hpp"
#include "travail/ui/TextField.hpp"

using namespace travail;

GameScene::GameScene() :
    Scene("Game"), m_Buffer(std::make_shared<CommandBuffer>())
{
    add(m_Buffer);
}
GameScene::~GameScene() { }

void GameScene::draw() {
    mvwaddstr(stdscr, 0,0,"Game (Press ^Q to continue)");
    
    int width, height;
    getmaxyx(stdscr, height, width);
    
    m_Buffer->clear();
    m_Buffer->setPos(0, height - 1);
    m_Buffer->setDim(Dimensions2i(width - 1,1));
    
    std::basic_string<chtype> div;
    div.resize(width, static_cast<chtype>(' ') | A_STANDOUT);
    
    mvwaddchstr(stdscr, height - 2, 0, div.data());
#ifndef NDEBUG
    mvwaddstr(stdscr, height - 3, 0, "Return: ");
    mvwaddstr(stdscr, height - 4, 0, "  Char: ");
#endif
}

int GameScene::handle(int ch) {
#ifndef NDEBUG
    int width, height;
    getmaxyx(stdscr, height, width);
    mvwprintw(stdscr, height - 4, 8, "%d", ch); clrtoeol();
#endif
    if(ch == 17) {
        m_Stack->pop();
        return 0;
    }
    ch = m_Buffer->handle(ch);
#ifndef NDEBUG
    mvwprintw(stdscr, height - 3, 8, "%d", ch); clrtoeol();
    m_Buffer->updateCurs();
#endif
    switch(ch) {
    case 0:
        wrefresh(stdscr);
        return 0;
    case KEY_ENTER:
    case '\n':
    case '\r':
        m_Buffer->getHistory().add(m_Buffer->getContents());
        m_Buffer->clear();
        m_Buffer->draw();
        wrefresh(m_Window);
        return 0;
    default:
        return ch;
    }
}
