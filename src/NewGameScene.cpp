
#include "travail/ui/scenes/NewGameScene.hpp"

#include <cctype>
#include "travail/graphics/Curses.hpp"
#include "travail/ui/InputField.hpp"
#include "travail/ui/Label.hpp"
#include "travail/ui/Option.hpp"
#include "travail/ui/SceneStack.hpp"
#include "travail/util/Keys.hpp"

using namespace travail;

static const char * _g_str_help1 =
    "Press UP to move up a line, DOWN to move down a line";
static const char * _g_str_help2 =
    "Press TAB to move left, SHIFT+TAB to move right";


static int _pred_isheight(int ch) {
    return (std::isdigit(ch) || ch == '"' || ch == '\'');
}

NewGameScene::NewGameScene() {
    m_Row = new Row();
    m_Column = new Column();
    
    add(new Label(0,0,"::New Game",A_BOLD|A_STANDOUT));
    add(new Label(0,22,_g_str_help1));
    add(new Label(0,23,_g_str_help2));
    
    InputField * fld_Name = new InputField(0, 1, "Name:", A_BOLD, 40);
    fld_Name->setMaxLength(fld_Name->getDim().width);
    
    InputField * fld_Age = new InputField(0, 3, "Age:", A_BOLD, 4);
    fld_Age->setMaxLength(fld_Age->getDim().width);
    fld_Age->setPredicate(&(std::isdigit));
    InputField * fld_Height = new InputField(10,3,"Height:", A_BOLD, 10);
    fld_Height->setMaxLength(fld_Height->getDim().width);
    fld_Height->setPredicate(&_pred_isheight);
    InputField * fld_Weight = new InputField(29,3,"Weight:", A_BOLD, 10);
    fld_Weight->setMaxLength(fld_Weight->getDim().width);
    fld_Weight->setPredicate(&(std::isdigit));
    
    Option * opt_Gender = new Option(0,2);
    opt_Gender->setSelectedAttrib(A_BOLD | A_UNDERLINE);
    opt_Gender->setUnselectedAttrib(A_BOLD);
    opt_Gender->add("Male");
    opt_Gender->add("Female");
    
    m_Column->wrap(false);
    m_Row->add(fld_Age);
    m_Row->add(fld_Height);
    m_Row->add(fld_Weight);

    m_Column->add(fld_Name);
    m_Column->add(opt_Gender);
    m_Column->add(m_Row);
    m_Column->add(new Label(76,21,"Next", A_BOLD));

    add(m_Column);
}

NewGameScene::~NewGameScene() { }

int NewGameScene::handle(int ch) {
    if(ch == travail::cntrl('q')) {
        m_Running = false;
        m_Stack->pop();
        return 0;
    }
    
    switch(m_Column->handle(ch)) {
    case KEY_ENTER:
    case '\n':
    case '\r':
        if(m_Column->getFocusedIndex() == m_Column->getChildren().size() - 1) {
            m_Stack->swap("Game");
            m_Running = false;
            return 0;
        }
        break;
    case 0:
        wrefresh(stdscr);
        return 0;
    }
    return ch;
}
