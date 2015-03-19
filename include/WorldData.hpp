#ifndef LEVEL_DATA_HPP
#define LEVEL_DATA_HPP

#include "Debug.h"
#include <unistd.h>
#include <fstream>

#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>
#include <json/json.h>

class WorldData
{
public:
    WorldData();

    void loadFromFile(const std::string& filename);
    void json2Vec(Json::Value &root, const std::string& fieldName, std::vector<std::vector<int>> &destination);

    const std::vector<std::vector<int>> getMap() const {return map;};
    const std::vector<std::vector<int>> getCollidables() const {return collidables;};

    const std::string getSheet() const {return spriteSheet;};
    
    const int getHeight() const {return map.size() * tileSize;}
    const int getWidth() const {return map[0].size() * tileSize;}
    const int getTileSize() const {return tileSize;};
    const sf::Vector2i getSpawnPosition() {return playerSpawnPosition;}

private:
    std::string spriteSheet;
    std::vector<std::vector<int>> map;   
    std::vector<std::vector<int>> collidables;
    int tileSize;
    sf::Vector2i playerSpawnPosition;
};



#endif