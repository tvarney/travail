
#ifndef TRAVAIL_UTIL_KEYS_HPP
#define TRAVAIL_UTIL_KEYS_HPP

namespace travail {
    /**
     * \brief Modify the character given to be the result of a control
     * sequence.
     * 
     * This function modifies the character given as if it was returned by
     * ncurses \c getch() when the user pressed the letter \c ch represents
     * while holding the control key. This is only guaranteed to work
     * accurately for values of \c ch for which \c std::isalpha(ch) would
     * return true.
     * 
     * \arg \c ch The character to modify
     * \return The character with only the first 5 bits allowed
     */
    constexpr unsigned char cntrl(unsigned char ch) {
        return ch & 0x1F;
    }
    /**
     * \brief Modify the character given to be the result of a meta sequence.
     * 
     * This function modifies the character given as if it was returned by
     * ncurses \c getch when the user pressed the letter \c ch represents while
     * holding the meta/alt key. This is only guaranteed to work accurately for
     * values of \c ch for which std::isalpha(ch) would return true.
     * 
     * \arg \c ch The character to modify
     * \return The character with the high bit set
     */
    constexpr unsigned char meta(unsigned char ch) {
        return ch | 0x80;
    }
}

#endif
