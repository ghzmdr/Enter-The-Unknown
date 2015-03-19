#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP


#include "Debug.h"
#include <map>
#include <string>
#include <memory>

typedef const std::string ID;

template<typename Resource>
class ResourceManager
{
public:
    Resource& operator[](ID id)
    {return get(id);}

private:    
    Resource& get(ID id);
    void load(ID id);
    std::map<std::string, std::unique_ptr<Resource>> resources;
};

template<typename Resource>
void ResourceManager<Resource>::load(ID id)
{
    std::unique_ptr<Resource> resource{new Resource()};
    check(resource->loadFromFile(id), "Failed to load resource: %s", id.c_str());
    auto inserted = resources.insert(std::make_pair(id, std::move(resource)));
    check(inserted.second, "Failed to insert resource: %s", id.c_str());
}

template<typename Resource>
Resource& ResourceManager<Resource>::get(ID id) 
{
    if (resources.count(id) < 1) 
    {
        load(id);
        return *resources[id];
    }
    auto found = resources.find(id);
    check(found != resources.end(), "Failed to retrieve resource by id: %s", id.c_str());
    return *found->second;
}

#endif