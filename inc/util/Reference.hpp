
#ifndef TRAVAIL_UTIL_REFERENCE_HPP
#define TRAVAIL_UTIL_REFERENCE_HPP

namespace travail {
    template <typename T>
    class Reference {
    public:
        Reference(T &value) :
            m_Pointer(&value)
        { }
        Reference(const Reference &source) :
            m_Pointer(source.m_Pointer)
        { }
        ~Reference() { }
        
        Reference<T> & operator=(const Reference<T> &rhs) {
            m_Pointer = rhs.m_Pointer;
        }
        Reference<T> & operator=(const T &rhs) {
            m_Pointer = &rhs;
        }
        
        bool operator>(const Reference<T> &rhs) const {
            return m_Pointer > rhs.m_Pointer;
        }
        bool operator<(const Reference<T> &rhs) const {
            return m_Pointer < rhs.m_Pointer;
        }
        bool operator==(const Reference<T> &rhs) const {
            return m_Pointer == rhs.m_Pointer;
        }
        bool operator!=(const Reference<T> &rhs) const {
            return m_Pointer != rhs.m_Pointer;
        }
        bool operator>=(const Reference<T> &rhs) const {
            return m_Pointer >= rhs.m_Pointer;
        }
        bool operator<=(const Reference<T> &rhs) const {
            return m_Pointer <= rhs.m_Pointer;
        }
        
        void set(const Reference<T> &rhs) {
            m_Pointer = rhs.m_Pointer;
        }
        void set(T &rhs) {
            m_Pointer =  &rhs;
        }
        
        T & get() const {
            return *m_Pointer;
        }
        const T & cget() const {
            return *m_Pointer;
        }
    protected:
        T * m_Pointer;
    };
}

#endif
