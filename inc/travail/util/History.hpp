
#ifndef TRAVAIL_HISTORY_HPP
#define TRAVAIL_HISTORY_HPP

#include <list>
#include <string>

namespace travail {
    class History {
    public:
        typedef std::list<std::string> HistoryList;
        typedef HistoryList::iterator Iterator;
        typedef HistoryList::const_iterator ConstIterator;
        
    public:
        History();
        History(std::size_t max_lines);
        History(bool keep_duplicates);
        History(std::size_t max_lines, bool keep_duplicates);
        ~History();
        
        bool getKeepDuplicates() const;
        void setKeepDuplicates(bool yes);
        std::size_t getMaxSize() const;
        void setMaxSize(std::size_t size);
        
        std::size_t size() const;
        
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        
        ConstIterator cbegin() const;
        ConstIterator cend() const;
        
        std::string & get(std::size_t index);
        
        void add(const std::string &str);
    protected:
        bool m_Duplicates;
        std::size_t m_MaxItems;
        HistoryList m_History;
    };
}

#endif
