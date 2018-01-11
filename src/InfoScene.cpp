
#include "travail/ui/scenes/InfoScene.hpp"

#include "travail/graphics/Curses.hpp"
#include "travail/ui/SceneStack.hpp"

using namespace travail;

const char * get_terminal_name() {
    const char * name = termname();
    if(!name) name = "Unknown";
    return name;;
}
const char * get_terminal_desc() {
    const char * desc = longname();
    if(!desc) desc = "";
    return desc;
}

InfoScene::InfoScene() { }
InfoScene::~InfoScene() { }

void InfoScene::draw() {
    int term_has_colors = ::has_colors();
    mvprintw(0,0,"Terminal Information: Press any key to return");
    mvprintw(1,0,"Name: %s", ::get_terminal_name());
    mvprintw(2,0,"Description: %s", ::get_terminal_desc());
    mvprintw(4,0,"Has Colors: %s", (term_has_colors ? "Yes" : "No"));
    if(has_colors()) {
        mvprintw(5,0, "  Colors: %d", COLORS);
        mvprintw(6,0, "   Pairs: %d", COLOR_PAIRS);
    }
}

int InfoScene::handle(int ch) {
    m_Stack->pop();
    return 0;
}
