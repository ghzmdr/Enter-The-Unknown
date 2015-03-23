#ifndef BOUNDING_ENTITY_HPP
#define BOUNDING_ENTITY_HPP

#include "Entities/GameObject.hpp"
#include "Components/GraphicsComponent.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Obstacle : public GameObject, public sf::Drawable
{
public:
    Obstacle(GraphicsComponent *gr, sf::Vector2f position, sf::Vector2i size);


private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    GraphicsComponent *graphics;
};


#endif