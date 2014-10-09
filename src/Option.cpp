
#include "ui/Option.hpp"

#include <algorithm>
#include "util/Keys.hpp"

using namespace travail;

Option::Option(Window *w) :
    Option(Point2i(0,0), w)
{ }
Option::Option(Orientation o, Window *w) :
    Option(o, Point2i(0,0), w)
{ }
Option::Option(int x, int y, Window *w) :
    Option(Point2i(x,y), w)
{ }
Option::Option(Orientation o, int x, int y, Window *w) :
    Option(o, Point2i(x,y), w)
{ }
Option::Option(const Point2i &origin, Window *w) :
    Option(Orientation::Horizontal, origin, w)
{ }
Option::Option(Orientation o, const Point2i &orig, Window *w) :
    Widget(orig, Dimensions2i(0,0), w),
    m_Orient(o), m_AttrOn(A_UNDERLINE), m_AttrOff(0),
    m_Index(0)
{ }

Option::~Option() { }

void Option::add(const std::string &optstr) {
    int attr = ((m_Choices.size() == 0) ? m_AttrOn : m_AttrOff);
    Point2i itemorig;
    if(m_Orient == Orientation::Horizontal) {
        // Calculate option position
        itemorig.x = m_Origin.x + m_Dim.width;
        itemorig.y = m_Origin.y;
        // Calculate new size
        m_Dim = Dimensions2i(static_cast<int>(optstr.size() + 1), 1);
    }else {
        // Calculate option position
        itemorig.x = m_Origin.x;
        itemorig.y = m_Origin.y + m_Dim.height;
        // Calculate new size
        int strlen = static_cast<int>(optstr.size());
        m_Dim.height += 1;
        m_Dim.width = (strlen > m_Dim.width ? strlen : m_Dim.width);
    }
    // Construct the label
    m_Choices.emplace_back(itemorig,optstr, attr);
}
void Option::remove(const std::string &optstr) {
    auto iter = m_Choices.begin();
    // List isn't sorted, best we can do is linear search
    while(iter != m_Choices.end()) {
        if((*iter).getText().getString() == optstr) {
            break;
        }
        iter++;
    }
    //auto iter = std::find(m_Choices.begin(), m_Choices.end(), optstr);
    if(iter != m_Choices.end()) {
        int shift = 0;
        if(m_Choices.size() > 1) {
            // Check if we need to change our choice index
            // This happens when the removed element is behind the current
            // choice, or when the current choice is being removed and
            // it is at the end of our choices.
            std::size_t distance = std::distance(m_Choices.begin(), iter);
            if((distance == m_Index && m_Index == m_Choices.size()) ||
               (distance < m_Index))
            {
                m_Index -= 1;
            }
            // Move all labels after iter back by one
            // Calculate how much to shift the items
            shift = static_cast<int>((*iter).getDim().width) + 1;
            auto niter = iter; //< Copy the iterator
            while(niter != m_Choices.end()) {
                Label &label = *niter;
                label.setPos(label.getPos().x - shift, m_Origin.y);
                niter++;
            }
            
            // Make sure that the current choice is still highlighted
            m_Choices[m_Index].setAttr((int)m_AttrOn);
        }
        
        m_Choices.erase(iter);
        // Change our dimensions
        if(m_Orient == Orientation::Horizontal) {
            // Horizontal option just removes the shift length
            m_Dim.width -= shift;
        }else {
            // Vertical reduces height by 1
            m_Dim.height -= 1;
            int strlen = static_cast<int>(optstr.size());
            if(strlen == m_Dim.width) {
                // If our strlen was the longest, scan for new longest
                strlen = 0;
                for(Label &label : m_Choices) {
                    if(label.getDim().width > strlen) {
                        strlen = label.getDim().width;
                    }
                }
                m_Dim.width = strlen;
            }
        }
    }
}

void Option::setPos(int x, int y) {
    // For each label in our choices, subtract current x origin from value
    // and add new x origin
    if(m_Orient == Orientation::Horizontal) {
        for(Label &label : m_Choices) {
            label.setPos(label.getPos().x - m_Origin.x + x, y);
        }
    }else {
        for(Label &label : m_Choices) {
            label.setPos(x, label.getPos().y - m_Origin.y + y);
        }
    }
    m_Origin = Point2i(x,y);
}
void Option::setPos(const Point2i &pos) {
    setPos(pos.x, pos.y);
}

bool Option::setChoice(int index) {
    if(index >= 0 && index < static_cast<int>(m_Choices.size()) &&
       static_cast<std::size_t>(index) != m_Index)
    {
        m_Choices[m_Index].setAttr(m_AttrOff);
        m_Choices[m_Index].draw();
        m_Choices[index].setAttr(m_AttrOn);
        m_Choices[index].draw();
        m_Index = index;
        travail::move(getCursor());
        return true;
    }
    return false;
}

int Option::getSelectedAttrib() const {
    return m_AttrOn;
}
void Option::setSelectedAttrib(int attr) {
    if(attr == m_AttrOn) {
        return;
    }
    
    m_AttrOn = attr;
    if(!(m_Choices.empty())) {
        m_Choices[m_Index].setAttr(attr);
    }
}
int Option::getUnselectedAttrib() const {
    return m_AttrOff;
}
void Option::setUnselectedAttrib(int attr) {
    if(attr == m_AttrOff) {
        return;
    }
    
    m_AttrOff = attr;
    std::size_t len = m_Choices.size();
    for(std::size_t i = 0; i < m_Index; ++i) {
        m_Choices[i].setAttr(attr);
    }
    for(std::size_t i = m_Index + 1; i < len; ++i) {
        m_Choices[i].setAttr(attr);
    }
}
const std::string & Option::getChosenStr() const {
    static std::string _invalid = "";
    if(!(m_Choices.empty())) {
        return m_Choices[m_Index].getText().getString();
    }else {
        return _invalid;
    }
}

int Option::getChosenInt() const {
    return static_cast<int>(m_Index);
}

void Option::draw() {
    for(Label &label : m_Choices) {
        label.draw();
    }
}

int Option::handle(int ch) {
    switch(m_Orient) {
    default:
    case Orientation::Horizontal:
        switch(ch) {
        case travail::cntrl('b'):
        case KEY_LEFT:
            return (setChoice(m_Index - 1) ? 0 : ch);
        case travail::cntrl('f'):
        case KEY_RIGHT:
            return (setChoice(m_Index + 1) ? 0 : ch);
        default:
            return ch;
        }
    case Orientation::Vertical:
        switch(ch) {
        case travail::cntrl('p'):
        case KEY_UP:
            return (setChoice(m_Index - 1) ? 0 : ch);
        case travail::cntrl('n'):
        case KEY_DOWN:
            return (setChoice(m_Index + 1) ? 0 : ch);
        default:
            return ch;
        }
    }
    return ch;
}

Point2i Option::getCursor() const {
    if(m_Choices.empty()) {
        return Widget::getCursor();
    }
    return m_Choices[m_Index].getCursor();
}
