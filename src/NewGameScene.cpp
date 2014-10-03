
#include "ui/scenes/NewGameScene.hpp"

#include <cctype>
#include "ui/Column.hpp"
#include "ui/Row.hpp"
#include "ui/SceneStack.hpp"
#include "util/Curses.hpp"
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
    m_Weight(29,3,"Weigth:",A_BOLD,10),
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
}
NewGameScene::~NewGameScene() { }

void NewGameScene::run() {
    Column column;
    column.wrap(false);
    
    Row row1;
    row1.add(m_Age);
    row1.add(m_Height);
    row1.add(m_Weight);
    
    column.add(m_Name);
    column.add(m_Gender);
    column.add(row1);
    column.add(m_LabelNext);
    
    m_LabelTitle.draw();
    m_LabelHelp1.draw();
    m_LabelHelp2.draw();
    
    column.draw();
    
    wrefresh(stdscr);
    
    int ch;
    while((ch = travail::wgetch(stdscr)) != travail::cntrl('q')) {
        switch(column.handle(ch)) {
        case KEY_ENTER:
        case '\n':
        case '\r':
            if(&column.getFocused() == &m_LabelNext) {
                m_Stack->pop();
                return;
            }else {
                column.next();
            }
            break;
        case 0:
            wrefresh(stdscr);
            break;
        }
    }
    //TODO: Move back to MainMenu if the loop exits
    m_Stack->pop();
}
