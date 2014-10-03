
#include "util/Curses.hpp"

#include <string>

namespace travail {
    namespace _fn_private {
        static std::string eraser;
    }
}

using namespace travail;

int travail::wgetch(Window *window, int metadelay) {
    int ch = ::wgetch(window);
    if(ch == 27) { //< Meta character/escape
        // Not portable, wont work if NCURSES_OPAQUE is defined as TRUE
        int delay = window->_delay;
        ::wtimeout(window, metadelay);
        int nch = ::wgetch(window);
        ::wtimeout(window, delay);
        
        if(nch != ERR) {
            if(nch < 128) {
                ch = 0x80 | nch; //< Return the character with the high-bit set
            }else {
                ch = nch; //< Return the character un-modified
            }
        }
    }
    return ch;
}

void travail::erase(Window *window, const Point2i &origin, int nchars) {
    // Clip nchars to width of window (sanity check, still may run over)
    nchars = (nchars > getmaxx(window) ? getmaxx(window) : nchars);
    // Resize our eraser string if needed
    if(nchars > static_cast<int>(_fn_private::eraser.size())) {
        _fn_private::eraser.resize(getmaxx(window), ' ');
    }
    // Write the eraser string with the given size to the window
    mvwaddnstr(window, origin.y, origin.x, _fn_private::eraser.data(), nchars);
}
void travail::erase(Window *window, const Point2i &origin,
                    const Dimensions2i &dim)
{
    // Clip nchars to width of window (sanity check, still may run over)
    int nchars = (dim.width > getmaxx(window) ? getmaxx(window) : dim.width);
    // Resize our eraser string if needed
    if(nchars > static_cast<int>(_fn_private::eraser.size())) {
        _fn_private::eraser.resize(getmaxx(window), ' ');
    }
    // Write the eraser string to the given area of the window
    for(int i = 0; i < dim.height; ++i) {
        mvwaddnstr(window, origin.y + i, origin.x, _fn_private::eraser.data(),
                   nchars);
    }
}

void travail::move(Window *window, const Point2i &pos) {
    wmove(window, pos.y, pos.x);
}
void travail::move(const Point2i &pos) {
    wmove(stdscr, pos.y, pos.x);
}
