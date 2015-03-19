#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>


class GameObject : public sf::Sprite
{

public:
    GameObject();
    GameObject(sf::Texture &texture);
    GameObject(sf::Texture &texture, sf::IntRect texRect);

    void setTextureRect(sf::IntRect rect);

    float left();
    float right();
    float top();
    float bottom();

    sf::Vector2i getSize();

protected:
    bool collidable;
};
#endif