
#include "travail/io/TagMap.hpp"

using namespace travail;

TagMap::Tag::Tag(const TagMap &map, uint32_t id) :
    map(&map), data(nullptr), id(id)
{ }
TagMap::Tag::Tag(const Tag &source) :
    map(source.map), data(source.data), id(source.id)
{ }
TagMap::Tag::~Tag() { }

TagMap::Tag & TagMap::Tag::operator=(const Tag &tag) {
    map = tag.map;
    data = tag.data;
    id = tag.id;
    return *this;
}

bool TagMap::Tag::operator==(const std::string &string) const {
    return *data == string;
}

bool TagMap::Tag::operator==(const Tag &tag) const {
    // If we are in the same map, with the same id, we are the same
    return (((map == tag.map) && (id == tag.id)) || (*data == *(tag.data)));
}

TagMap::TagMap() { }
TagMap::~TagMap() { }

TagMap::Iterator TagMap::find(const std::string &string) {
    return m_Tags.find(string);
}

TagMap::Tag TagMap::get(const std::string &string) {
    MapType::value_type item(string, TagMap::Tag(*this, m_Tags.size()));
    // Pair, first -> iterator, second -> bool
    auto result = m_Tags.insert(item);
    if(result.second == true) {
        // Set the data pointer of the tag to the key string
        result.first->second.data = &(result.first->first);
    }
    // Return a copy
    return result.first->second;
}
