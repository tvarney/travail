
#include "travail/Application.hpp"

#ifndef NDEBUG
# include <iostream>
# include <fstream>
#endif

int main(int argc, char **argv) {
#ifndef NDEBUG
    std::ofstream out("cout.txt");
    std::streambuf *buff = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
#endif
    
    travail::Application app;
    int rval = app.run(argc, argv);

#ifndef NDEBUG
    std::cout.rdbuf(buff);
#endif
    
    return rval;
}
