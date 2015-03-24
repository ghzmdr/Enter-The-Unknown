#ifndef FLOOR_LOADER_HPP
#define FLOOR_LOADER_HPP

#include <SFML/System/Vector2.hpp>
#include "Utils/JsonParser.hpp"
#include "Factories/EntityFactory.hpp"

class FloorLoader : private JsonParser
{
public:
    FloorLoader(const std::string &filename);

    std::vector<std::vector<short>> getMap();
    std::vector<std::vector<short>> getCollidables();

    std::string getTileSheetFileName();
    
    unsigned short getTileSize();

    std::vector<EnemyData> getEnemies();

    sf::Vector2i getFloorSize();
    sf::Vector2i getSpawnPosition();
    sf::Vector2i getExitPosition();
private:
    void json2WorldMap(const std::string &field, std::vector<std::vector<short>> &destination);
};

#endif
