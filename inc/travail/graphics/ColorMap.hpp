
#ifndef TRAVAIL_GRAPHICS_COLOR_MAP_HPP
#define TRAVAIL_GRAPHICS_COLOR_MAP_HPP

namespace travail {
    class ColorMap {
    public:
        enum Mode {
            Current = -1,
            Colors8 = 0,
            Colors16 = 1,
            Colors88 = 2,
            Colors256 = 3
        };
        
    public:
        ColorMap();
        ~ColorMap();
        
        int & operator[](int colorid);
        const int & operator[](int colorid) const;
        
        void colors(Mode mode);
        
        int & map(int index);
        const int & map(int index) const;
        int & map(int index, Mode dest);
        const int & map(int index, Mode dest) const;
    protected:
        Mode m_NumColors;
        int * m_Mapping;
        int m_Mappings[1024];
    };
}

#endif
