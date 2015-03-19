#include "Utils/JsonParser.hpp"

JsonParser::JsonParser(const std::string &filename)
: filename{filename}
{
    std::ifstream file{filename, std::ifstream::binary};
    
    if (!reader.parse(file, root))
    {
        printf("Could not parse json: %s", filename.c_str());  
        exit(EXIT_FAILURE);
    }
}

float JsonParser::getNumber(const std::string &field)
{
    float ret = root.get(field, -9999).asFloat();
    err_default(ret != -9999);
    return ret;
}

std::string JsonParser::getString(const std::string &field)
{
    std::string ret = root.get(field, "null").asString();
    err_default(ret != "null");
    return ret;
}

sf::Vector2i JsonParser::getVector(const std::string &field)
{
    Json::Value jSize = root.get(field, false);
    err_default(jSize != false);

    short   x = jSize.get("X", -9999).asInt(),
            y = jSize.get("Y", -9999).asInt();

    std::string tmpField = field + "->X";
    jsonErrMsg(x != -9999, filename, tmpField);

    tmpField = field + "->Y";
    jsonErrMsg(y != -9999, filename, tmpField);

    return {x, y};
}