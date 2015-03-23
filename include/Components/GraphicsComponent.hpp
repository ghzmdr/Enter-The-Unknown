#ifndef GRAPHICS_COMPONENT_HPP
#define GRAPHICS_COMPONENT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Components/Component.hpp"
#include "Entities/GameObject.hpp"

class Entity;

class GraphicsComponent : public Component
{
public:
    GraphicsComponent(sf::Texture &texture, sf::IntRect textureRect);

    virtual void update(GameObject &parent);

    sf::Texture texture;
    sf::VertexArray drawable;
private:

    sf::FloatRect textureRect;
};


#endif

