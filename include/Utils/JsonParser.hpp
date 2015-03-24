#ifndef JSON_PARSER
#define JSON_PARSER

#include <json/json.h>

#include <SFML/System/Vector2.hpp>

#include <fstream>
#include <string>
#include <vector>


class JsonParser
{
public:
    JsonParser(const std::string &filename);
protected:
    float getNumber(const std::string &field);
    std::string getString(const std::string &field);
    sf::Vector2i getVector(const std::string &field);

    Json::Value root;
    Json::Reader reader;
    std::string filename;
};

static void jsonErrMsg(bool condition, std::string &filename, const std::string &field)
{
    if (!condition)
    {
        printf("[!ERROR!] Could not read field %s from %s\n", field.c_str(), filename.c_str());
        //exit(-1);
    }
}



#define err_default(C) jsonErrMsg(C, filename, field);

#endif
