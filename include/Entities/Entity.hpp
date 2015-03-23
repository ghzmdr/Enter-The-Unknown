#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/GraphicsComponent.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <memory>

class Floor;
class PhysicsComponent;

class Entity : public GameObject, public sf::Drawable
{
public:
    const float diagonalFactor = 1.3, runFactor = 1.5;

public:
    Entity(MovementComponent *mv, PhysicsComponent *ph, GraphicsComponent *gr);

    sf::Vector2f velocity;
    float speed;
    bool moving, running, canRun;

    float lastSpeed;

    virtual void update(Floor &floor);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    MovementComponent *movement;
    PhysicsComponent *physics;
    GraphicsComponent *graphics;
};

#endif