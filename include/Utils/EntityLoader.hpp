#ifndef ENEMY_LOADER_HPP
#define ENEMY_LOADER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Utils/JsonParser.hpp"

class EntityLoader : private JsonParser
{
public:
    EntityLoader(const std::string &filename);

    u_short getLives();
    u_short getPower();
    
    float getSpeed();
    
    sf::Vector2i getSize();
    
    const std::string getScriptFilename();
    const std::string getSheetFileName();

    std::vector<u_short> getMovementFrames();
    std::vector<u_short> getAttackFrames();
    std::vector<u_short> getDeathFrames();

private:
    void loadFrames();
    void loadSubFrames(const std::string &subField, std::vector<u_short> &destination);
    
    Json::Value jFrames;
};

#endif