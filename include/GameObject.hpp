#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Utils/Utility.hpp"


class GameObject : public sf::Sprite
{

public:
    GameObject(){};
    GameObject(sf::Texture &texture){setTexture(texture);};
    GameObject(sf::Texture &texture, sf::IntRect texRect){setTexture(texture); setTextureRect(texRect);}

    void setTextureRect(sf::IntRect rect)
    {sf::Sprite::setTextureRect(rect); centerOrigin(*this);}

    bool isCollidable() const;
    void setCollidable(bool val);

    float left()      {return getPosition().x - getTextureRect().width/2;}
    float right()     {return getPosition().x + getTextureRect().width/2;}    
    float top()       {return getPosition().y - getTextureRect().height/2;}
    float bottom()    {return getPosition().y + getTextureRect().height/2;}

    sf::Vector2i getSize()   {return {getTextureRect().width, getTextureRect().height};}

private:
    bool collidable;
};
#endif