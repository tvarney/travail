
#include "travail/graphics/Curses.hpp"
#include "travail/ui/SceneStack.hpp"
#include "travail/ui/scenes/GameScene.hpp"
#include "travail/ui/scenes/InfoScene.hpp"
#include "travail/ui/scenes/MainMenu.hpp"
#include "travail/ui/scenes/NewGameScene.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    std::ofstream out("cout.txt");
    std::streambuf *buff = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    std::cout << "main(): Initializing NCurses..." << std::endl;
    travail::init_curses();

    std::cout << "main(): Initializing SceneStack..." << std::endl;
    travail::SceneStack stack;

    std::cout << "main(): Adding scenes to SceneStack..." << std::endl;
    stack.add("MainMenu", std::make_shared<travail::MainMenu>());
    stack.add("NewGame", std::make_shared<travail::NewGameScene>());
    stack.add("Game", std::make_shared<travail::GameScene>());
    stack.add("Info", std::make_shared<travail::InfoScene>());

    std::cout << "main(): Setting stack window instance..." << std::endl;
    stack.setWindow(stdscr);

    std::cout << "main(): Pushing MainMenu onto top of stack..." << std::endl;
    stack.push("MainMenu");
    std::cout << "main(): Calling SceneStack::run()..." << std::endl;
    stack.run();

    std::cout << "main(): Calling ::endwin()..." << std::endl;
    endwin();

    std::cout << "main(): Restoring Streambuf and exiting function..." <<
        std::endl;
    std::cout.rdbuf(buff);
    
    return 0;
}
