
#include "graphics/Curses.hpp"
#include "ui/SceneStack.hpp"
#include "ui/scenes/MainMenu.hpp"

int main(int argc, char **argv) {
    travail::init_curses();
    
    travail::SceneStack stack;
    travail::MainMenu mainmenu;
    stack.push(mainmenu);
    stack.run();
    
    endwin();
    
    return 0;
}
