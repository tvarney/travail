
#include "travail/util/History.hpp"

using namespace travail;

History::History() :
    History(1000, false)
{ }
History::History(std::size_t max_lines) :
    History(max_lines, false)
{ }
History::History(bool keep_duplicates) :
    History(1000, keep_duplicates)
{ }
History::History(std::size_t max_lines, bool keep_duplicates) :
    m_Duplicates(keep_duplicates), m_MaxItems(max_lines)
{ }
History::~History() { }

bool History::getKeepDuplicates() const {
    return m_Duplicates;
}
void History::setKeepDuplicates(bool yes) {
    m_Duplicates = yes;
}

std::size_t History::getMaxSize() const {
    return m_MaxItems;
}
void History::setMaxSize(std::size_t lines) {
    if(lines < m_MaxItems) {
        while(m_History.size() > lines) {
            m_History.pop_back();
        }
    }
    m_MaxItems = lines;
}

std::size_t History::size() const {
    return m_History.size();
}

History::Iterator History::begin() {
    return m_History.begin();
}
History::Iterator History::end() {
    return m_History.end();
}
History::ConstIterator History::begin() const {
    return m_History.begin();
}
History::ConstIterator History::end() const {
    return m_History.end();
}
History::ConstIterator History::cbegin() const {
    return m_History.cbegin();
}
History::ConstIterator History::cend() const {
    return m_History.cend();
}

std::string & History::get(std::size_t index) {
    auto iter = m_History.begin();
    for(std::size_t i = 0; i < index; ++i) {
        iter++;
    }
    return *(iter);
}

void History::add(const std::string &str) {
    if(false == m_Duplicates) {
        // Check for duplicates
        if(m_History.size() > 0 && str == m_History.front()) {
            // Don't add duplicate
            return;
        }
    }
    
    // Either not a duplicate or we are fine with duplicates in history
    while(m_History.size() >= m_MaxItems) {
        m_History.pop_back();
    }
    m_History.push_front(str);
}
