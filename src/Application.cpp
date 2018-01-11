
#include "travail/Application.hpp"

#include "travail/graphics/Curses.hpp"
#include "travail/ui/scenes/InfoScene.hpp"
#include "travail/ui/scenes/GameScene.hpp"
#include "travail/ui/scenes/MainMenu.hpp"
#include "travail/ui/scenes/NewGameScene.hpp"

using namespace travail;

Application::Application() {
    m_SceneStack.add("Info", std::make_shared<InfoScene>());
    m_SceneStack.add("Game", std::make_shared<GameScene>());
    m_SceneStack.add("MainMenu", std::make_shared<MainMenu>());
    m_SceneStack.add("NewGame", std::make_shared<NewGameScene>());
}
Application::~Application() { }

int Application::run(int argc, char **argv) {
    load_config();
    if((m_ExitCode = parse_args(argc, argv))) {
        return m_ExitCode;
    }
    return mainloop();
}

int Application::parse_args(int argc, char **argv) {
    return 0;
}

void Application::load_config() { }

int Application::mainloop() {
    travail::init_curses();
    
    m_SceneStack.setWindow(stdscr);
    
    if(m_SceneStack.size() == 0) {
        m_SceneStack.push("MainMenu");
    }

    m_Running = true;
    m_ExitCode = 0;
    //m_SceneStack.run();

    int ch;
    while(m_Running) {
        if(m_SceneStack.size() == 0) {
            m_Running = false;
            break;
        }
        ch = travail::wgetch(stdscr);
        m_SceneStack.peek()->handle(ch);
    }
    
    endwin();
    
    return m_ExitCode;
}
