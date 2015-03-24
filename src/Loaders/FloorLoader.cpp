#include "Loaders/FloorLoader.hpp"
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

std::vector<EnemyData> FloorLoader::getEnemies()
{
    std::vector<EnemyData> ret;
    std::string field = "enemies";
    Json::Value enemyArray = root.get(field, false);
    err_default(enemyArray != false);

    for (int i = 0; i < enemyArray.size(); i++)        
    {
        std::string field = "kind";
        std::string kind = enemyArray[i].get(field, "null").asString();
        err_default(kind != "null");

        field = "position";
        Json::Value pos = enemyArray[i].get(field, false);
        err_default(pos != false);

        field = "X";
        float px = pos.get(field, -9999).asFloat();
        err_default(px != -9999);

        field = "Y";
        float py = pos.get(field, -9999).asFloat();
        err_default(py != -9999);

        ret.push_back({kind, {px, py}});
    }

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
