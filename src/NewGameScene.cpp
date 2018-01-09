
#include "ui/scenes/NewGameScene.hpp"

#include <cctype>
#include "graphics/Curses.hpp"
#include "ui/Column.hpp"
#include "ui/Row.hpp"
#include "ui/SceneStack.hpp"
#include "util/Keys.hpp"

using namespace travail;

static int _pred_isheight(int ch) {
    return (std::isdigit(ch) || ch == '"' || ch == '\'');
}

NewGameScene::NewGameScene() :
    m_LabelTitle(0,0,"::New Game", A_BOLD|A_STANDOUT),
    m_LabelHelp1(0,22,"Press UP to move up a line, DOWN to move down a line"),
    m_LabelHelp2(0,23,"Press TAB to move left, SHIFT+Tab to move right"),
    m_Name(0,1,"Name:",A_BOLD,40),
    m_Age(0,3,"Age:",A_BOLD,4),
    m_Height(10,3,"Height:",A_BOLD,10),
    m_Weight(29,3,"Weight:",A_BOLD,10),
    m_Gender(0,2),
    m_LabelNext(76,21, "Next", A_BOLD)
{
    m_Name.setMaxLength(m_Name.getDim().width);
    m_Age.setMaxLength(m_Age.getDim().width);
    m_Age.setPredicate(&(std::isdigit));
    m_Height.setMaxLength(m_Height.getDim().width); //5'6", 5.123", etc
    m_Height.setPredicate(&_pred_isheight);
    m_Weight.setMaxLength(m_Height.getDim().width); // 163.0001
    m_Weight.setPredicate(&(std::isdigit));
    
    m_Gender.setSelectedAttrib(A_BOLD | A_UNDERLINE);
    m_Gender.setUnselectedAttrib(A_BOLD);
    m_Gender.add("Male");
    m_Gender.add("Female");

    m_Column.wrap(false);
    m_Row.add(m_Age);
    m_Row.add(m_Height);
    m_Row.add(m_Weight);

    m_Column.add(m_Name);
    m_Column.add(m_Gender);
    m_Column.add(m_Row);
    m_Column.add(m_LabelNext);
}
NewGameScene::~NewGameScene() { }

void NewGameScene::run() {
    m_LabelTitle.draw();
    m_LabelHelp1.draw();
    m_LabelHelp2.draw();
    
    m_Column.draw();
    
    wrefresh(stdscr);
    
    int ch;
    m_Running = true;
    while(m_Running) {
        ch = travail::wgetch(stdscr);
        handle(ch);
    }
    //TODO: Move back to MainMenu if the loop exits
    m_Stack->pop();
}

void NewGameScene::handle(int ch) {
    if(ch == travail::cntrl('q')) {
        m_Running = false;
        m_Stack->pop();
        return;
    }
    
    switch(m_Column.handle(ch)) {
    case KEY_ENTER:
    case '\n':
    case '\r':
        if(&m_Column.getFocused() == &m_LabelNext) {
            m_Stack->swap("Game");
            m_Running = false;
            return;
        }
        break;
    case 0:
        wrefresh(stdscr);
        break;
    }
}
