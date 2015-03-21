#ifndef ENEMY_LOADER_HPP
#define ENEMY_LOADER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Utils/JsonParser.hpp"

class EntityLoader : private JsonParser
{
public:
    EntityLoader(const std::string &filename);

    unsigned short getLives();
    unsigned short getPower();

    float getSpeed();

    sf::Vector2i getSize();

    const std::string getScriptFilename();
    const std::string getSheetFileName();

    std::vector<unsigned short> getMovementFrames();
    std::vector<unsigned short> getAttackFrames();
    std::vector<unsigned short> getDeathFrames();

private:
    void loadFrames();
    void loadSubFrames(const std::string &subField, std::vector<unsigned short> &destination);

    Json::Value jFrames;
};

#endif
