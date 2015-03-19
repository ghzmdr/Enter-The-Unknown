#ifndef ENEMY_LOADER_HPP
#define ENEMY_LOADER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <json/json.h>
#include <fstream>

class EnemyLoader
{
public:
    EnemyLoader(const std::string &filename);

    u_short getDamage();
    u_short getLives();
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


    Json::Value root;
    Json::Reader reader;
    std::string filename;

    Json::Value jFrames;
};

#endif