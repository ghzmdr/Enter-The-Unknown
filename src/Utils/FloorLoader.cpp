#include "Utils/FloorLoader.hpp"
#include "Debug.h"

FloorLoader::FloorLoader(const std::string &filename)
: JsonParser{filename}
{}

std::vector<std::vector<short>> FloorLoader::getMap()
{
    const std::string field = "map";
    std::vector<std::vector<short>> ret;
    json2WorldMap(field, ret);
    err_default(!ret.empty());
    return ret;
}

std::vector<std::vector<short>> FloorLoader::getCollidables()
{
    std::vector<std::vector<short>> ret;
    json2WorldMap("collidables", ret);
    return ret;
}


std::string FloorLoader::getTileSheetFileName()
{return getString("tilesheet");}

unsigned short FloorLoader::getTileSize()
{return getNumber("tilesize");}

sf::Vector2i FloorLoader::getFloorSize()
{
    sf::Vector2i ret;
    auto map = getMap();
    ret.y = map.size();
    ret.x = map[0].size();
    auto tileSize = getTileSize();
    ret.x *= tileSize;
    ret.y *= tileSize;
    return ret;
}

sf::Vector2i FloorLoader::getSpawnPosition()
{return getVector("spawn");}

sf::Vector2i FloorLoader::getExitPosition()
{return getVector("exit");}

void FloorLoader::json2WorldMap(const std::string &field, std::vector<std::vector<short>> &destination)
{
    Json::Value jsonMap = root.get(field, false);
    err_default(jsonMap != false);

    //Construct map vector one row at a time by looping trough json array
    for (int i = 0; i < jsonMap.size(); i++)
    {
        std::vector<short> row;
        for(int  j = 0; j < jsonMap[i].size(); j++)
            row.push_back(jsonMap[i][j].asInt());
        destination.push_back(row);
    }
}
