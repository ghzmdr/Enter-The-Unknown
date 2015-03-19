#include "Utils/EntityLoader.hpp"
#include "Debug.h"


EntityLoader::EntityLoader(const std::string &filename)
:JsonParser{filename}, jFrames{false}
{}

u_short EntityLoader::getDamage()
{return getNumber("damage");}

u_short EntityLoader::getLives()
{return getNumber("lives");}

float EntityLoader::getSpeed()
{return getNumber("speed");}

sf::Vector2i EntityLoader::getSize()
{return getVector("size");}

const std::string EntityLoader::getScriptFilename()
{return getString("script");}

const std::string EntityLoader::getSheetFileName()
{return getString("sheet");}



std::vector<u_short> EntityLoader::getMovementFrames()
{        
    std::vector<u_short> ret;
    loadSubFrames("movement", ret);
    return ret;
}

std::vector<u_short> EntityLoader::getAttackFrames()
{
    std::vector<u_short> ret;
    loadSubFrames("attack", ret);
    return ret;
}

std::vector<u_short> EntityLoader::getDeathFrames()
{
    std::vector<u_short> ret;
    loadSubFrames("death", ret);
    return ret;
}

void EntityLoader::loadFrames()
{
    std::string field = "animation";
    jFrames = root.get(field, false);
    err_default(jFrames != false);
}

void EntityLoader::loadSubFrames(const std::string &subField, std::vector<u_short> &destination)
{
    if (jFrames == false) loadFrames();
    std::string field = "animation->"+subField;
    Json::Value jMFrames = jFrames.get(subField, false);
    err_default(jMFrames != false);

    for (auto fVal : jMFrames)
        destination.push_back(fVal.asInt());
    
    err_default(!destination.empty());
}