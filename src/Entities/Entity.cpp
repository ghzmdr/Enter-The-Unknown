#include "Entities/Entity.hpp"

#include "Components/PhysicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Floor.hpp"

Entity::Entity(MovementComponent *mv,PhysicsComponent *ph, GraphicsComponent *gr)
: physics{ph}, movement{mv}, graphics{gr}{speed = 2, canRun = true;}

void Entity::update(Floor &floor)
{
    movement->update(*this);
    
    if (velocity.x != 0)
        lastSpeed = velocity.x;
    else if (velocity.y != 0)
        lastSpeed = velocity.y;
    else lastSpeed = 0;

    physics->update(*this, floor);

    position.x += velocity.x;
    position.y += velocity.y;    

    graphics->update(*this);

    velocity.x = 0; velocity.y = 0;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.texture = &(graphics->texture);
    target.draw(graphics->drawable, states);
}