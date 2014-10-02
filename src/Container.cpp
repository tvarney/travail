
#include "ui/Container.hpp"

using namespace travail;

Container::Container(Window *w) :
    Widget(w)
{ }
Container::Container(Point2i &orig, Dimensions2i &dim, Window *win) :
    Widget(orig, dim, win)
{ }
Container::~Container() { }
