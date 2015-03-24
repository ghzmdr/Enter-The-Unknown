#include "Entities/Entity.hpp"

#include "Components/PhysicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Floor.hpp"

Entity::Entity( std::unique_ptr<MovementComponent> mv,
                std::unique_ptr<PhysicsComponent> ph,
                std::unique_ptr<GraphicsComponent> gr, 
                std::unique_ptr<AnimationComponent> an)
: movement{std::move(mv)},
  physics{std::move(ph)},
graphics{std::move(gr)}, 
animation{std::move(an)}
{}

void Entity::update(Floor &floor)
{
    canRun = true;
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