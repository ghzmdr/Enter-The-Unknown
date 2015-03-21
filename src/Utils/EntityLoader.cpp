#include "Utils/EntityLoader.hpp"
#include "Debug.h"


EntityLoader::EntityLoader(const std::string &filename)
:JsonParser{filename}, jFrames{false}
{}

unsigned short EntityLoader::getLives()
{return getNumber("lives");}

unsigned short EntityLoader::getPower()
{return getNumber("damage");}

float EntityLoader::getSpeed()
{return getNumber("speed");}

sf::Vector2i EntityLoader::getSize()
{return getVector("size");}

const std::string EntityLoader::getScriptFilename()
{return getString("script");}

const std::string EntityLoader::getSheetFileName()
{return getString("sheet");}



std::vector<unsigned short> EntityLoader::getMovementFrames()
{
    std::vector<unsigned short> ret;
    loadSubFrames("movement", ret);
    return ret;
}

std::vector<unsigned short> EntityLoader::getAttackFrames()
{
    std::vector<unsigned short> ret;
    loadSubFrames("attack", ret);
    return ret;
}

std::vector<unsigned short> EntityLoader::getDeathFrames()
{
    std::vector<unsigned short> ret;
    loadSubFrames("death", ret);
    return ret;
}

void EntityLoader::loadFrames()
{
    std::string field = "animation";
    jFrames = root.get(field, false);
    err_default(jFrames != false);
}

void EntityLoader::loadSubFrames(const std::string &subField, std::vector<unsigned short> &destination)
{
    if (jFrames == false) loadFrames();
    std::string field = "animation->"+subField;
    Json::Value jMFrames = jFrames.get(subField, false);
    err_default(jMFrames != false);

    for (auto fVal : jMFrames)
        destination.push_back(fVal.asInt());

    err_default(!destination.empty());
}
