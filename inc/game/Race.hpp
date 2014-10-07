
#ifndef TRAVAIL_GAME_RACE_HPP
#define TRAVAIL_GAME_RACE_HPP

#include <string>

namespace travail {
    class Race {
    public:
        Race(const std::string &name);
        ~Race();

        const std::string & name() const;
    private:
        std::string m_Name;
    };
}

#endif
