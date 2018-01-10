
#pragma once
#ifndef TRAVAIL_APPLICATION_HPP
#define TRAVAIL_APPLICATION_HPP

#include "travail/ui/SceneStack.hpp"

namespace travail {
    class Application {
    public:
        Application();
        ~Application();

        int run(int argc, char **argv);

        int parse_args(int argc, char **argv);
        void load_config();
        int mainloop();
    private:
        SceneStack m_SceneStack;
        bool m_Running;
        int m_ExitCode;
    };
}

#endif
