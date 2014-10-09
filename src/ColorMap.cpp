
#include "graphics/ColorMap.hpp"

#include <cstring>

using namespace travail;

namespace {
    extern int _gs_DefaultMapping[1024];
}

ColorMap::ColorMap() :
    m_NumColors(ColorMap::Colors256), m_Mapping((int*)(&m_Mappings)+(256*3))
{
    // Copy default mapping into our mapping
    std::memcpy(this->m_Mappings, ::_gs_DefaultMapping, 1024*sizeof(int));
}
ColorMap::~ColorMap() { }

int & ColorMap::operator[](int colorid) {
    return m_Mapping[colorid & 0xFF];
}
const int & ColorMap::operator[](int colorid) const {
    return m_Mapping[colorid & 0xFF];
}

void ColorMap::colors(ColorMap::Mode mode) {
    if(m_NumColors != mode && mode >= 0 && mode <= Colors256) {
        m_NumColors = mode;
        m_Mapping = (int*)(&m_Mappings)+(256*mode);
    }
}

int & ColorMap::map(int index) {
    return m_Mapping[index & 0xFF];
}
const int & ColorMap::map(int index) const {
    return m_Mapping[index & 0xFF];
}

int & ColorMap::map(int index, ColorMap::Mode mode) {
    Mode m = (mode == ColorMap::Current ? m_NumColors : mode);
    return ((int*)(&m_Mappings)+(256*m))[index & 0xFF];
}
const int & ColorMap::map(int index, ColorMap::Mode mode) const {
    Mode m = (mode == ColorMap::Current ? m_NumColors : mode);
    return ((int*)(&m_Mappings)+(256*m))[index & 0xFF];
}

// Default mapping - Generated using CIEL*ab color distances and simple color
// cubes
namespace {
int _gs_DefaultMapping[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 7, 1, 2, 3, 4, 5, 6, 7, 0, 4, 4, 4, 4, 4, 2, 6, 6,
    6, 4, 4, 2, 6, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 2, 2, 2, 6,
    6, 6, 1, 5, 5, 4, 4, 4, 3, 7, 6, 5, 5, 5, 3, 6, 6, 6, 6, 7, 2, 6, 6, 6, 6,
    6, 2, 2, 6, 6, 6, 6, 2, 2, 2, 6, 6, 6, 1, 5, 5, 5, 5, 4, 3, 7, 7, 5, 5, 5,
    3, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 3, 6, 6, 7, 7, 2, 2, 2, 6, 6, 7, 1,
    5, 5, 5, 5, 5, 3, 7, 7, 5, 5, 5, 3, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 3,
    7, 7, 7, 7, 3, 3, 3, 7, 7, 7, 1, 5, 5, 5, 5, 5, 1, 1, 5, 5, 5, 5, 3, 7, 7,
    7, 7, 5, 3, 3, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7, 3, 3, 3, 7, 7, 7, 1, 1, 5, 5,
    5, 5, 1, 1, 5, 5, 5, 5, 3, 7, 7, 7, 7, 5, 3, 3, 7, 7, 7, 7, 3, 3, 7, 7, 7,
    7, 3, 3, 3, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
    4, 4, 4, 12, 12, 2, 6, 8, 8, 4, 4, 2, 6, 6, 6, 6, 6, 2, 2, 6, 6, 6, 6, 10,
    2, 14, 14, 14, 14, 10, 2, 2, 14, 14, 14, 1, 5, 5, 4, 4, 12, 3, 8, 8, 8, 5,
    5, 3, 8, 8, 8, 8, 8, 2, 6, 6, 6, 6, 15, 2, 2, 14, 14, 6, 6, 10, 2, 14, 14,
    14, 14, 1, 5, 5, 5, 13, 13, 3, 8, 8, 8, 5, 5, 3, 8, 8, 8, 8, 8, 3, 3, 15,
    15, 15, 15, 11, 3, 15, 15, 15, 15, 10, 2, 14, 14, 14, 14, 1, 5, 5, 5, 13,
    13, 3, 8, 8, 5, 5, 5, 3, 8, 8, 15, 15, 15, 3, 3, 15, 15, 15, 15, 11, 3, 15,
    15, 15, 15, 11, 3, 3, 7, 7, 7, 9, 5, 5, 5, 13, 13, 1, 8, 8, 5, 5, 5, 3, 15,
    15, 15, 15, 15, 3, 3, 15, 15, 15, 15, 11, 3, 15, 15, 15, 15, 11, 3, 3, 7,
    7, 7, 9, 1, 5, 5, 13, 13, 9, 1, 8, 5, 5, 5, 3, 15, 15, 15, 15, 5, 3, 3, 15,
    15, 15, 15, 11, 3, 15, 15, 15, 15, 11, 3, 3, 7, 7, 7, 0, 0, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 15, 15, 15, 15, 15, 15, 15, 15, 0, 1, 2, 3, 4,
    5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 17, 17, 18, 18, 12, 20, 21, 22,
    23, 23, 23, 20, 25, 21, 22, 22, 23, 24, 25, 25, 26, 27, 27, 24, 29, 25, 30,
    26, 27, 10, 29, 29, 30, 30, 14, 32, 33, 33, 34, 35, 35, 36, 8, 38, 39, 39,
    39, 40, 41, 42, 43, 38, 23, 40, 41, 41, 42, 43, 43, 44, 45, 46, 46, 47, 27,
    44, 45, 45, 46, 46, 47, 32, 49, 33, 34, 34, 35, 52, 53, 54, 55, 55, 55, 36,
    57, 83, 38, 38, 39, 40, 41, 41, 42, 43, 43, 40, 61, 41, 62, 42, 43, 44, 45,
    45, 46, 46, 47, 48, 49, 49, 50, 51, 51, 52, 53, 54, 55, 55, 55, 52, 73, 53,
    54, 54, 55, 56, 57, 57, 84, 59, 59, 60, 61, 57, 62, 63, 59, 60, 61, 61, 62,
    62, 63, 48, 65, 49, 66, 50, 51, 68, 69, 70, 70, 71, 71, 52, 73, 53, 54, 54,
    55, 72, 73, 73, 74, 75, 75, 56, 77, 57, 78, 15, 59, 60, 61, 61, 62, 62, 63,
    9, 65, 65, 66, 66, 13, 68, 69, 70, 70, 71, 71, 68, 73, 69, 70, 70, 71, 72,
    73, 73, 74, 75, 75, 72, 77, 73, 78, 74, 75, 11, 77, 77, 78, 78, 7, 0, 0,
    81, 81, 81, 81, 81, 8, 8, 8, 82, 37, 37, 37, 83, 83, 83, 83, 84, 84, 84,
    84, 58, 58, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
    75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
    94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124,
    125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154,
    155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
    170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184,
    185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214,
    215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
    230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244,
    245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};
}
