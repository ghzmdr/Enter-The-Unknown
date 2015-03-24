#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/AnimationComponent.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#define DIAGONAL_FACTOR 1.3

class Floor;
class PhysicsComponent;

class Entity : public GameObject, public sf::Drawable
{
public:
    //This should be initialized dinamically, and use default values only ad a fallback

public:
    Entity( std::unique_ptr<MovementComponent> mv, 
            std::unique_ptr<PhysicsComponent> ph, 
            std::unique_ptr<GraphicsComponent> gr, 
            std::unique_ptr<AnimationComponent> an);

    //Properties
    float speed, runFactor;

    //State holding variables
    sf::Vector2f velocity;
    float lastSpeed;
    bool moving, running, canRun;

    virtual void update(Floor &floor);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    std::unique_ptr<MovementComponent> movement;
    std::unique_ptr<PhysicsComponent> physics;
    std::unique_ptr<GraphicsComponent> graphics;
    std::unique_ptr<AnimationComponent> animation;
};

#endif