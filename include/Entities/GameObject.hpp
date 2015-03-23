#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/System/Vector2.hpp>

class GameObject 
{
public:
    GameObject(){};
    sf::Vector2f position, size;

    float left()    {return position.x - size.x /2;}
    float right()   {return position.x + size.x /2;}
    float top()     {return position.y - size.y /2;}
    float bottom()  {return position.y + size.y /2;}
};
#endif