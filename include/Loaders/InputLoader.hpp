#ifndef INPUT_LOADER_HPP
#define INPUT_LOADER_HPP

#include "Utils/JsonParser.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>


class InputLoader : private JsonParser
{
public:
    InputLoader();

    sf::Keyboard::Key getKDown();
    sf::Keyboard::Key getKUp();
    sf::Keyboard::Key getKRight();
    sf::Keyboard::Key getKLeft();

    sf::Keyboard::Key getKRun();
    sf::Keyboard::Key getKPrimary();
    sf::Keyboard::Key getKSecondary();

    unsigned int getJRun();
    unsigned int getJPrimary();
    unsigned int getJSecondary();

    Json::Value keyboard;
    Json::Value joystick;

private:
    std::string getFromKeyboard(const std::string &field);
    std::string getFromJoystick(const std::string &field);
    sf::Keyboard::Key toKey(const std::string button);
};

#endif