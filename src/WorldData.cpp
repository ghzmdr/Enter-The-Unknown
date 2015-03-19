#include "World.hpp"

WorldData::WorldData()
{loadFromFile("data/zone.json");}

void WorldData::loadFromFile(const std::string& filename)
{
    Json::Value root;
    Json::Reader reader;
    
    //Open file and parse it
    std::ifstream file(filename, std::ifstream::binary);
    check(reader.parse(file, root), "Couldn't parse json");
    
    json2Vec(root, "map", map);
    json2Vec(root, "collidables", collidables);      

    //Retrieve tile size
    tileSize = root.get("tileSize", -1).asInt();
    check(tileSize>0, "Couldn't read tileSize");
    log_info("TileSize: %d", tileSize);

    //Retrieve tileset filename
    spriteSheet = root.get("tileSet", "null").asString();
    check(spriteSheet != "null", "Couldn't read tilesheet filename");
    log_info("TileSet: %s", spriteSheet.c_str());

    Json::Value jPlayerSpawnPosition = root.get("spawnPosition", false);
    check(jPlayerSpawnPosition, "Couldn't read spawn position");
    playerSpawnPosition.x = jPlayerSpawnPosition["x"].asFloat();
    playerSpawnPosition.y = jPlayerSpawnPosition["y"].asFloat();
}

void WorldData::json2Vec(Json::Value &root, const std::string& fieldName, std::vector<std::vector<int>> &destination)
{
    //Retrieve map
    Json::Value jsonMap = root.get(fieldName, false);
    check(jsonMap, "Couldn't read %s from json", fieldName.c_str());

    //Construct map vector one row at a time by looping trough json array
    for (int i = 0; i < jsonMap.size(); i++)
    {
        std::vector<int> row;
        for(int  j = 0; j < jsonMap[i].size(); j++)
            row.push_back(jsonMap[i][j].asInt());

        destination.push_back(row);
    }
}
