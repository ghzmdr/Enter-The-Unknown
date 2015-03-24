#include "Loaders/InputLoader.hpp"

InputLoader::InputLoader()
: JsonParser("config/input.json")
{
    std::string field = "KEYBOARD";
    keyboard = root.get(field, "NONE");
    err_default(keyboard != "NONE");

    field = "CONTROLLER";
    joystick = root.get(field, "NONE");
    err_default(joystick != "NONE");
}

sf::Keyboard::Key InputLoader::getKDown()
{return toKey(getFromKeyboard("DOWN"));}

sf::Keyboard::Key InputLoader::getKUp()
{return toKey(getFromKeyboard("UP"));}

sf::Keyboard::Key InputLoader::getKLeft()
{return toKey(getFromKeyboard("LEFT"));}

sf::Keyboard::Key InputLoader::getKRight()
{return toKey(getFromKeyboard("RIGHT"));}

sf::Keyboard::Key InputLoader::getKPrimary()
{return toKey(getFromKeyboard("PRIMARY"));}

sf::Keyboard::Key InputLoader::getKSecondary()
{return toKey(getFromKeyboard("SECONDARY"));}

sf::Keyboard::Key InputLoader::getKRun()
{return toKey(getFromKeyboard("RUN"));}

#define BTN_CASE(A)  if (button == A) return sf::Keyboard::

sf::Keyboard::Key InputLoader::toKey(const std::string button)
{
    BTN_CASE("UP") Up;
    else BTN_CASE("DOWN") Down;
    else BTN_CASE("RIGHT") Right;
    else BTN_CASE("LEFT") Left;
    else BTN_CASE("A") A;
    else BTN_CASE("B") B;
    else BTN_CASE("C") C;
    else BTN_CASE("D") D;
    else BTN_CASE("E") E;
    else BTN_CASE("F") F;
    else BTN_CASE("G") G;
    else BTN_CASE("H") H;
    else BTN_CASE("I") I;
    else BTN_CASE("J") J;
    else BTN_CASE("K") K;
    else BTN_CASE("L") L;
    else BTN_CASE("M") M;
    else BTN_CASE("N") N;
    else BTN_CASE("O") O;
    else BTN_CASE("P") P;
    else BTN_CASE("Q") Q;
    else BTN_CASE("R") R;
    else BTN_CASE("S") S;
    else BTN_CASE("T") T;
    else BTN_CASE("U") U;
    else BTN_CASE("V") V;
    else BTN_CASE("W") W;
    else BTN_CASE("X") X;
    else BTN_CASE("Y") Y;
    else BTN_CASE("Z") Z;
    
    else BTN_CASE("SPACE") Space;

    else BTN_CASE("LCTRL") LControl;
    else BTN_CASE("RCTRL") RControl;

    else BTN_CASE("LSHIFT") LShift;
    else BTN_CASE("RSHiFT") RShift;
}

std::string InputLoader::getFromKeyboard(const std::string &field)
{
    std::string v = keyboard.get(field, "NONE").asString();
    err_default(v != "NONE");
    return v;
}

std::string InputLoader::getFromJoystick(const std::string &field)
{
    std::string v = joystick.get(field, "NONE").asString();
    err_default(v != "NONE");
    return v;
}