
#include "graphics/Curses.hpp"
#include "ui/SceneStack.hpp"
#include "ui/scenes/GameScene.hpp"
#include "ui/scenes/InfoScene.hpp"
#include "ui/scenes/MainMenu.hpp"
#include "ui/scenes/NewGameScene.hpp"

#include <iostream>

int main(int argc, char **argv) {
    travail::init_curses();
    
    travail::SceneStack stack;
    travail::MainMenu mainmenu;
    if(!stack.add("MainMenu", std::make_shared<travail::MainMenu>())) {
        std::cout << "Could not add 'MainMenu'" << std::endl;
    }
    if(!stack.add("NewGame", std::make_shared<travail::NewGameScene>())) {
        std::cout << "Could not add 'NewGame'" << std::endl;
    }
    if(!stack.add("Game", std::make_shared<travail::GameScene>())) {
        std::cout << "Could not add 'Game'" << std::endl;
    }
    if(!stack.add("Info", std::make_shared<travail::InfoScene>())) {
        std::cout << "Could not add 'Info'" << std::endl;
    }
    
    stack.push("MainMenu");
    stack.run();
    
    endwin();
    
    return 0;
}
