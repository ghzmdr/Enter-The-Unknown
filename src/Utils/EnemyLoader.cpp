#include "Utils/EnemyLoader.hpp"
#include "Debug.h"


static void jsonErrMsg(bool condition, std::string &filename, std::string &field)
{check(condition, "Couldn't read field %s from %s", field.c_str(), filename.c_str());}

#define err_default(C) jsonErrMsg(C, filename, field);

EnemyLoader::EnemyLoader(const std::string &filename)
:filename{filename}, jFrames{false}
{
    std::ifstream file(filename, std::ifstream::binary);
    check(reader.parse(file, root), "Couldn't parse json: %s", filename.c_str());    
}

u_short EnemyLoader::getDamage()
{
    std::string field = "damage";
    u_short damage = root.get(field, -1).asInt();
    err_default(damage >=0);
    return damage;
}

u_short EnemyLoader::getLives()
{
    std::string field = "lives";
    u_short lives = root.get(field, -1).asInt();
    err_default(lives >= 0);
    return lives;
}


float EnemyLoader::getSpeed()
{
    std::string field = "speed";
    float speed = root.get(field, -1).asFloat();
    err_default(speed >= 0);
    return speed;
}

sf::Vector2i EnemyLoader::getSize()
{
    std::string field = "size";
    Json::Value jSize = root.get(field, false);
    err_default(jSize != false);

    short   x = jSize.get("W", -1).asInt(),
            y = jSize.get("H", -1).asInt();

    std::string tmpField = field + "->W";
    jsonErrMsg(x >=0, filename, tmpField);

    tmpField = field + "->H";
    jsonErrMsg(y >=0, filename, tmpField);

    return {x, y};
}

const std::string EnemyLoader::getScriptFilename()
{
    std::string field = "script";
    std::string script = root.get("script", "null").asString();
    err_default(script != "null");
    return script;
}

const std::string EnemyLoader::getSheetFileName()
{
    std::string field = "sheet";
    std::string sheet = root.get("sheet", "null").asString();
    err_default(sheet != "null");
    return sheet;
}

std::vector<u_short> EnemyLoader::getMovementFrames()
{        
    std::vector<u_short> ret;
    loadSubFrames("movement", ret);
    return ret;
}

std::vector<u_short> EnemyLoader::getAttackFrames()
{
    std::vector<u_short> ret;
    loadSubFrames("attack", ret);
    return ret;
}

std::vector<u_short> EnemyLoader::getDeathFrames()
{
    std::vector<u_short> ret;
    loadSubFrames("death", ret);
    return ret;
}

void EnemyLoader::loadFrames()
{
    std::string field = "animation";
    jFrames = root.get(field, false);
    err_default(jFrames != false);
}

void EnemyLoader::loadSubFrames(const std::string &subField, std::vector<u_short> &destination)
{
    if (jFrames == false) loadFrames();
    std::string field = "animation->"+subField;
    Json::Value jMFrames = jFrames.get(subField, false);
    err_default(jMFrames != false);

    log_info("IRUN");

    for (auto fVal : jMFrames)
        destination.push_back(fVal.asInt());
    
    err_default(!destination.empty());
}