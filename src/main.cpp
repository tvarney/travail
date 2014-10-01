
#include "ui/SceneStack.hpp"
#include "ui/scenes/MainMenu.hpp"
#include "util/Curses.hpp"

int main(int argc, char **argv) {
    initscr();
    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
    }
    
    raw();
    noecho();
    keypad(stdscr, 1);
    ESCDELAY = 50;
    
    travail::SceneStack stack;
    travail::MainMenu mainmenu;
    stack.push(mainmenu);
    stack.run();
    
    endwin();
    
    return 0;
}
