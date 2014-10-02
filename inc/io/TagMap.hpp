
#ifndef TRAVAIL_IO_TAG_HPP
#define TRAVAIL_IO_TAG_HPP

#include <stdint.h>
#include <string>
#include <unordered_map>

namespace travail {
    class TagMap {
    public:
        struct Tag {
            Tag(const TagMap &map, uint32_t id);
            Tag(const Tag &source);
            ~Tag();
            
            Tag & operator=(const Tag &tag);
            
            bool operator==(const std::string &string) const;
            bool operator==(const Tag &tag) const;
            
            const TagMap *map;
            const std::string *data;
            uint32_t id;
        };
        
        typedef std::unordered_map<std::string, Tag> MapType;
        typedef MapType::iterator Iterator;
        
    public:
        TagMap();
        ~TagMap();
        
        Iterator find(const std::string &string);
        Tag get(const std::string &string);
        
    protected:
        MapType m_Tags;
    };
}

#endif
