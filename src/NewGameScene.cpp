
#include "ui/scenes/NewGameScene.hpp"

#include "ui/SceneStack.hpp"
#include "util/Curses.hpp"
#include "util/Keys.hpp"

using namespace travail;

NewGameScene::NewGameScene() :
    m_LabelTitle(0,0,"::New Game", A_BOLD|A_STANDOUT),
    m_LabelHelp1(0,22,"Press UP to move up a line, DOWN to move down a line"),
    m_LabelHelp2(0,23,"Press TAB to move left, SHIFT+Tab to move right"),
    m_Name(0,1,"Name:",A_BOLD,40),
    m_Age(0,2,"Age:",A_BOLD,4),
    m_Height(10,2,"Height:",A_BOLD,10),
    m_Weight(29,2,"Weigth:",A_BOLD,10)
{
    //m_TextName.setMaxChars(40);
    //m_TextAge.setMaxChars(4);
    //m_TextHeight.setMaxChars(10); //5'6", 5.123", etc
    //m_TextWeight.setMaxChars(10); // 163.0001
}
NewGameScene::~NewGameScene() { }

void NewGameScene::run() {
    m_LabelTitle.draw();
    m_LabelHelp1.draw();
    m_LabelHelp2.draw();
    m_Name.draw();
    m_Age.draw();
    m_Height.draw();
    m_Weight.draw();
    
    wrefresh(stdscr);
    
    int line = 0, row = 0;
    int ch;
    while((ch = getch()) != travail::cntrl('q')) {
        switch(ch) {
        case '\t':
        case KEY_BTAB:
        case KEY_UP:
        case KEY_DOWN:
            break;
        }
    }
    m_Stack->pop();
}
